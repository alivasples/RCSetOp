/* Copyright 2003-2017 GBDI-ICMC-USP <caetano@icmc.usp.br>
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*   http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include <arboretum/stMultiplePageManager.h>

template <class PageManager>
stMultiplePageManager<PageManager>::stMultiplePageManager(const string &fileName,
                                           u_int32_t pagesPerPM,
                                           u_int32_t pageSize) {
    string tempFileName;

    this->fileName = fileName;
    this->pagesPerPM = pagesPerPM;
    this->pageCount = 0;

    tempFileName.append(this->fileName).append(".0");

    this->PMs.push_back(new PageManager(tempFileName.c_str(),
                                        pageSize));
}

template <class PageManager>
stMultiplePageManager<PageManager>::stMultiplePageManager(const std::string &fileName,
                                           u_int32_t pagesPerPM) {
    int i;
    std::string tempFileName;

    this->fileName = fileName;
    this->pagesPerPM = pagesPerPM;
    this->pageCount = 0;

    tempFileName.append(this->fileName).append(".0");

    this->PMs.push_back(new PageManager(tempFileName.c_str()));
    this->pageCount += this->PMs.at(0)->GetPageCount();

    i = 0;

    while (this->PMs.at(i)->GetPageCount() == this->pagesPerPM) {
        ++i;
        tempFileName = "";

        tempFileName.append(this->fileName).append(".").append(to_string(i));

        try {
            this->PMs.push_back(new PageManager(tempFileName.c_str()));
        } catch (const exception &e) {
            break;
        }

        this->pageCount += this->PMs.at(i)->GetPageCount();
    }
}

template <class PageManager>
stMultiplePageManager<PageManager>::~stMultiplePageManager() {
    for (u_int32_t i = 0; i < this->PMs.size(); ++i) {
        delete this->PMs.at(i);
    }
}

template <class PageManager>
bool stMultiplePageManager<PageManager>::IsEmpty() {
    // Only the position 0 is checked.
    // If the first PM is empty, then the others are expected to be empty as well.
    return this->PMs.at(0)->IsEmpty();
}

template <class PageManager>
stPage* stMultiplePageManager<PageManager>::GetHeaderPage() {
    UpdateReadCounter();

    // The header is stored only in the first PM.
    // There is no need to store it in the other PMs.
    return this->PMs.at(0)->GetHeaderPage();
}

template <class PageManager>
stPage* stMultiplePageManager<PageManager>::GetPage(u_int32_t pageID) {
    u_int32_t pmID;
    u_int32_t actualPageID;
    stPage *page;

    pmID = GetCorrespondentPM(pageID);
    actualPageID = GetActualPageID(pageID);

    // Gets the page.
    page = this->PMs.at(pmID)->GetPage(actualPageID);

    // Replaces the actual ID with the logical ID.
    page->SetPageID(pageID);

    UpdateReadCounter();

    return page;
}

template <class PageManager>
void stMultiplePageManager<PageManager>::ReleasePage(stPage *page) {
    u_int32_t pmID;
    u_int32_t actualPageID;
    u_int32_t formerPageID;

    pmID = GetCorrespondentPM(page->GetPageID());
    actualPageID = GetActualPageID(page->GetPageID());

    formerPageID = page->GetPageID();

    page->SetPageID(actualPageID);
    this->PMs.at(pmID)->ReleasePage(page);
    page->SetPageID(formerPageID);
}

template <class PageManager>
stPage* stMultiplePageManager<PageManager>::GetNewPage() {
    u_int32_t currentPM;
    string newFileName;
    stPage *page;

    currentPM = this->PMs.size() - 1;

    if (this->PMs.at(currentPM)->GetPageCount() == this->pagesPerPM) {
        newFileName.append(this->fileName).append(".").append(to_string(++currentPM));

        this->PMs.push_back(new PageManager(newFileName.c_str(),
                                            GetMinimumPageSize()));
    }

    page = this->PMs.at(currentPM)->GetNewPage();
    ++this->pageCount;

    // Replaces the actual ID with the current logical ID.
    page->SetPageID(this->pageCount);

    UpdateWriteCounter();

    return page;
}

template <class PageManager>
void stMultiplePageManager<PageManager>::WritePage(stPage *page) {
    u_int32_t pmID;
    u_int32_t actualPageID;
    u_int32_t formerPageID;

    pmID = GetCorrespondentPM(page->GetPageID());
    actualPageID = GetActualPageID(page->GetPageID());

    formerPageID = page->GetPageID();

    page->SetPageID(actualPageID);
    this->PMs.at(pmID)->WritePage(page);
    page->SetPageID(formerPageID);

    UpdateWriteCounter();
}

template <class PageManager>
void stMultiplePageManager<PageManager>::WriteHeaderPage(stPage *headerPage) {
    // The header is stored only in the first PM.
    // There is no need to store it in the other PMs.
    this->PMs.at(0)->WriteHeaderPage(headerPage);

    UpdateWriteCounter();
}

template <class PageManager>
void stMultiplePageManager<PageManager>::DisposePage(stPage *page) {
    u_int32_t pmID;
    u_int32_t actualPageID;
    u_int32_t formerPageID;

    pmID = GetCorrespondentPM(page->GetPageID());
    actualPageID = GetActualPageID(page->GetPageID());

    formerPageID = page->GetPageID();

    page->SetPageID(actualPageID);
    this->PMs.at(pmID)->DisposePage(page);
    page->SetPageID(formerPageID);
}

template <class PageManager>
u_int32_t stMultiplePageManager<PageManager>::GetMinimumPageSize() {
    return PMs.at(0)->GetMinimumPageSize();
}

template <class PageManager>
u_int32_t stMultiplePageManager<PageManager>::GetPageCount() {
    return pageCount;
}

template <class PageManager>
void stMultiplePageManager<PageManager>::ResetStatistics() {
    for (u_int32_t i = 0; i < this->PMs.size(); ++i) {
        this->PMs.at(i)->ResetStatistics();
    }

    stPageManager::ResetStatistics();
}

template <class PageManager>
u_int32_t stMultiplePageManager<PageManager>::GetCorrespondentPM(u_int32_t logicalPageID) {
    // Header page.
    // The header is always stored in the first PM.
    if (logicalPageID == 0) {
        return 0;
    }

    u_int32_t fullPMsCount;
    u_int32_t pmID;

    // Number of full PMs.
    fullPMsCount = logicalPageID / this->pagesPerPM;

    // Identifies the correspondent PM.
    if (logicalPageID % this->pagesPerPM == 0) {
        pmID = fullPMsCount - 1;
    } else {
        pmID = fullPMsCount;
    }

    return pmID;
}

template <class PageManager>
u_int32_t stMultiplePageManager<PageManager>::GetActualPageID(u_int32_t logicalPageID) {
    // Header page.
    if (logicalPageID == 0) {
        return 0;
    }

    u_int32_t actualPageID;

    // Identifies the actual page within the correspondent PM.
    if (logicalPageID % this->pagesPerPM == 0) {
        actualPageID = this->pagesPerPM;
    } else {
        actualPageID = logicalPageID % this->pagesPerPM;
    }

    return actualPageID;
}

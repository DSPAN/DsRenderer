#include "rtti.h"
#include <iostream>
#include <algorithm>

Rtti::~Rtti() {
    for(auto iter = mFields.begin(); iter != mFields.end(); ++iter)
        delete(*iter);

    mFields.clear();
}

Field* Rtti::findField(const std::string& name) {
    auto foundElement = std::find_if(mFields.begin(), mFields.end(), [&name](Field* x) { return x->mName == name; });

    if(foundElement == mFields.end()) {
        std::cout<<"Cannot find a field with the specified name: " + name<<std::endl;
    }

    return *foundElement;
}

Field* Rtti::findField(int uniqueFieldId) {
    auto foundElement = std::find_if(mFields.begin(), mFields.end(), [&uniqueFieldId](Field* x) { return x->mUniqueId == uniqueFieldId; });

    if(foundElement == mFields.end())
        return nullptr;

    return *foundElement;
}

void Rtti::addNewField(Field* field) {
    if(field == nullptr) {
        std::cout<<"Field argument can't be null."<<std::endl;
    }

    int uniqueId = field->mUniqueId;
    auto foundElementById = std::find_if(mFields.begin(), mFields.end(), [uniqueId](Field* x) { return x->mUniqueId == uniqueId; });

    if(foundElementById != mFields.end()) {
        std::cout<<"Field with the same ID already exists."<<std::endl;
    }

    std::string& name = field->mName;
    auto foundElementByName = std::find_if(mFields.begin(), mFields.end(), [&name](Field* x) { return x->mName == name; });

    if(foundElementByName != mFields.end())
    {
        std::cout<<"Field with the same name already exists."<<std::endl;
    }

    mFields.push_back(field);
}

void Rtti::addPlainField(const std::string& name, uint32_t uniqueId) {
    Field* newField = new Field();
    newField->init(name, uniqueId);
    addNewField(newField);
}


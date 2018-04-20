#ifndef RTTIINFO_H
#define RTTIINFO_H

#include <string>
#include <vector>

struct Field
{
    void init(const std::string& name, uint16_t id) {
        this->mName = name;
        this->mUniqueId = id;
    }

    std::string mName;
    uint16_t mUniqueId;
};

class Rtti
{
public:
    Rtti() {}

    ~Rtti();

    virtual const std::string& getRTTIName() = 0;

    virtual uint32_t getRTTIId() = 0;

    Field* findField(const std::string& name);

    Field* findField(int uniqueFieldId);

    uint32_t getNumFields() const { return (uint32_t)mFields.size(); }

    Field* getField(uint32_t idx) { return mFields.at(idx); }

    void addNewField(Field* field);

    void addPlainField(const std::string& name, uint32_t uniqueId);

private:
    std::vector<Field*> mFields;
};

#endif // RTTIINFO_H

#ifndef TEXT_COLUMN_H
#define TEXT_COLUMN_H

#include "BaseColumn.h"


// Class for text columns
class TextColumn : public BaseColumn {
private:
    vector<string> textValues;
public:
    TextColumn();
    ~TextColumn() = default;

    virtual void addValueInColumn(const string& value) override;
    virtual const string getValueAtIndex(unsigned index) const override;

    virtual const vector<string> getColumn() const override;

    virtual const unsigned getSize() const override;
    virtual void removeValueAt(unsigned index) override;
    virtual const string getMinimalValue() const override;
    virtual const string getMaximalValue() const override;

    virtual const vector<unsigned> getIndexesOfSortedColumn(char s) const override;
};

#endif //TEXT_COLUMN_H
#ifndef DATE_COLUMN_H
#define DATE_COLUMN_H

#include "BaseColumn.h"

// Class for date columns
class DateColumn : public BaseColumn {
private:
    vector<string> dateValues;
public:
    DateColumn ();
    ~DateColumn () = default;

    virtual void addValueInColumn(const string& value) override;
    virtual const string getValueAtIndex(unsigned index) const override;

    virtual const vector<string> getColumn() const override;

    virtual const unsigned getSize() const override;
    virtual void removeValueAt(unsigned index) override;
    
    virtual const string getMinimalValue() const override;
    virtual const string getMaximalValue() const override;

    virtual const vector<unsigned> getIndexesOfSortedColumn(char s) const override;
};


#endif //DATE_COLUMN_H
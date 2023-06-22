#include "..\headers\BaseColumn.h"

BaseColumn::BaseColumn(const string& value) : typeOfColumn(value) {}

const string& BaseColumn::getTypeOfColumn() const {
    return typeOfColumn;
}
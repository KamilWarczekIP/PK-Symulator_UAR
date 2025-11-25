#include "listwithextremes.hpp"

ListWithExtremes::ListWithExtremes() {}
QList<QPointF>* ListWithExtremes::getList()
{
    return &this->list;
}
qreal ListWithExtremes::getMaxValue()
{
    return this->values.begin()->first;
}
qreal ListWithExtremes::getMinValue()
{
    return this->values.begin()->first;
}
void ListWithExtremes::appendLastValue(QPointF new_point)
{

}
void ListWithExtremes::deleteFirstValue()
{

    list.front();
    list.pop_front();
}

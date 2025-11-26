#include "listwithextremes.hpp"

ListWithExtremes::ListWithExtremes() {}
QList<QPointF>* ListWithExtremes::getList()
{
    return &this->list;
}
qreal ListWithExtremes::getMaxValue()
{
    return this->values.rbegin()->first;
}
qreal ListWithExtremes::getMinValue()
{
    return this->values.begin()->first;
}
void ListWithExtremes::appendLastValue(QPointF new_point)
{
    list.append(new_point);
    if(this->values.find(new_point.y()) == this->values.end())
        this->values[new_point.y()] = 0;

    this->values[new_point.y()]++;
}
void ListWithExtremes::deleteFirstValue()
{
    this->values[list.front().y()]--;

    if(this->values[list.front().y()] == 0)
        this->values.erase(list.front().y());

    list.pop_front();
}

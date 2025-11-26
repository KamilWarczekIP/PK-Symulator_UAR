#ifndef LISTWITHEXTREMES_HPP
#define LISTWITHEXTREMES_HPP
#include <qlist.h>
#include <qpoint.h>
#include <map>


class ListWithExtremes
{
    QList<QPointF> list;
    std::map<qreal, uint16_t> values;
public:
    ListWithExtremes();
    QList<QPointF>* getList();
    qreal getMaxValue();
    qreal getMinValue();
    void appendLastValue(QPointF new_point);
    void deleteFirstValue();
};

#endif // LISTWITHEXTREMES_HPP

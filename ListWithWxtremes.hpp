#ifndef LISTWITHWXTREMES_H
#define LISTWITHWXTREMES_H
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
    qreal max();
    qreal min();
    void appendLastValue(QPointF new_point);
    void deleteFirstValue();
    void clear();
};

#endif // LISTWITHWXTREMES_H

#ifndef SPMVOPERATION_H
#define SPMVOPERATION_H

#include <QString>
#include <QList>
#include "utilities.h"

#define COLIND_SIZE     sizeof(quint32)


class SpMVOperation
{
public:
    SpMVOperation(QString matrixName);
    ~SpMVOperation();

    quint32 rowCount() {return m_rowCount;}
    quint32 colCount() {return m_colCount;}
    quint32 nzCount() {return m_nzCount;}

    void assignWorkToWorker(quint32 peID, quint32 peCount, VectorIndex & startingRow, quint64 & startingNZ,
                            QList<VectorIndex> & dvAccessPattern, QList<VectorIndex> & rowLengths);

    static QList<VectorIndex> insertHazardAvoidanceBubbles(QList<VectorIndex> accessStream, int minSameElementSpacing);

    QList<VectorIndex> getDVAccessPattern(quint32 peID, quint32 peCount);
    QList<quint32> getRowLengths(quint32 peID, quint32 peCount);


protected:
    QString m_matrixName;
    quint32 m_rowCount, m_colCount, m_nzCount;
    quint32 * m_colIndices;
    quint32 * m_rowPointers;

    static void shiftActiveWindowAndInsert(VectorIndex * window, VectorIndex newElement, int windowSize);
    static bool windowContains(VectorIndex * window, VectorIndex element, int windowSize);
};

#endif // SPMVOPERATION_H

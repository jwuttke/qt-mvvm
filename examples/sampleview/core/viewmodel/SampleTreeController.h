#ifndef SAMPLETREECONTROLLER_H
#define SAMPLETREECONTROLLER_H

#include <QObject>
#include "LayerTableViewModel.h"
#include <QItemSelectionModel>
#include <set>

class SampleModel;

class SampleTreeController : public QObject
{
    Q_OBJECT
public:
    explicit SampleTreeController(SampleModel* model);
    ~SampleTreeController() override;

    LayerTableViewModel& viewModel() { return m_view_model; }
    QItemSelectionModel& selectionModel() { return m_selection_model; }

    void onCreateMultiLayer();
    void onCreateLayer();
    void onClone();
    void onRemove();

private:
    SampleModel* m_sample_model;
    LayerTableViewModel m_view_model;
    QItemSelectionModel m_selection_model;
};

#endif // SAMPLETREECONTROLLER_H

#include "datagraph.h"


// #################### Public ####################
DataGraph::DataGraph(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();
}

// #################### Private ###################
void DataGraph::createGuiItems()
{
    flow_chartView->setFixedSize(490, 398);
    press_chartView->setFixedSize(490, 398);
}

void DataGraph::createAndFillLayouts()
{
    hbox->addWidget(flow_chartView);
    hbox->addWidget(press_chartView);

    this->setLayout(hbox);
}
// #################### Signals ###################
// #################### Public slots ###############
// #################### Private slots ##############

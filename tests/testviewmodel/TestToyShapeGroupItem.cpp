// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toy_includes.h"
#include <QSignalSpy>
#include <mvvm/model/comboproperty.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/propertyviewmodel.h>
#include <mvvm/viewmodel/viewdataitem.h>
#include <mvvm/viewmodel/viewitems.h>

using namespace ModelView;

//! Tests of toy ShapeGroup in the context of model and viewmodel.

class ToyShapeGroupItemTest : public ::testing::Test
{
public:
    ~ToyShapeGroupItemTest();
};

ToyShapeGroupItemTest::~ToyShapeGroupItemTest() = default;

//! Toy multilayer as produced bo toy SampleModel.

TEST_F(ToyShapeGroupItemTest, initialState)
{
    ToyItems::ShapeGroupItem item;

    EXPECT_EQ(item.currentIndex(), 1);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_TRUE(item.data().isValid());
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.currentType(), ToyItems::Constants::SphereType);
    ASSERT_EQ(item.children().size(), 3);

    // parent child relationship
    EXPECT_EQ(item.children().at(0)->parent(), &item);
    EXPECT_EQ(item.children().at(1)->parent(), &item);
    EXPECT_EQ(item.children().at(2)->parent(), &item);

    // expected value in combo
    ComboProperty combo = item.data().value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);
    EXPECT_EQ(combo.values(),
              std::vector<std::string>({"Cylinder", "Full sphere", "Anysotropical pyramid"}));
}

TEST_F(ToyShapeGroupItemTest, setCurrentType)
{
    ToyItems::ShapeGroupItem item;
    item.setCurrentType(ToyItems::Constants::CylinderType);

    EXPECT_EQ(item.currentIndex(), 0);
    ASSERT_TRUE(item.currentItem() != nullptr);
    EXPECT_EQ(item.currentType(), item.currentItem()->modelType());
    EXPECT_EQ(item.currentItem()->modelType(), ToyItems::Constants::CylinderType);
    EXPECT_TRUE(item.data().isValid());
    EXPECT_EQ(item.children().size(), 3);

    // expected value in combo
    ComboProperty combo = item.data().value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 0);
    EXPECT_EQ(combo.values(),
              std::vector<std::string>({"Cylinder", "Full sphere", "Anysotropical pyramid"}));
}

TEST_F(ToyShapeGroupItemTest, inModelContext)
{
    ToyItems::SampleModel model;
    auto item = model.insertItem<ToyItems::ShapeGroupItem>();
    ASSERT_TRUE(item != nullptr);

    EXPECT_EQ(item->currentIndex(), 1);
    ASSERT_TRUE(item->currentItem() != nullptr);
    EXPECT_TRUE(item->data().isValid());
    EXPECT_EQ(item->currentType(), item->currentItem()->modelType());
    EXPECT_EQ(item->children().size(), 3);

    // parent child relationship
    EXPECT_EQ(item->children().at(0)->parent(), item);
    EXPECT_EQ(item->children().at(1)->parent(), item);
    EXPECT_EQ(item->children().at(2)->parent(), item);

    // model relationship
    EXPECT_EQ(item->children().at(0)->model(), &model);
    EXPECT_EQ(item->children().at(1)->model(), &model);
    EXPECT_EQ(item->children().at(2)->model(), &model);
}

TEST_F(ToyShapeGroupItemTest, setDataInModelContext)
{
    ToyItems::SampleModel model;
    auto item = model.insertItem<ToyItems::ShapeGroupItem>();
    ASSERT_TRUE(item != nullptr);

    // initial status
    EXPECT_EQ(item->currentIndex(), 1);
    EXPECT_EQ(item->currentType(), ToyItems::Constants::SphereType);
    ComboProperty combo = model.data(item, ItemDataRole::DATA).value<ComboProperty>();
    EXPECT_EQ(combo.currentIndex(), 1);

    // setting through combo
    combo.setCurrentIndex(0);
    model.setData(item, combo.variant(), ItemDataRole::DATA);

    EXPECT_EQ(item->currentIndex(), 0);
    EXPECT_EQ(item->currentType(), ToyItems::Constants::CylinderType);
}

//! ViewLabelItem and ViewDataItem from ShapeItem.

TEST_F(ToyShapeGroupItemTest, viewItemsFromShapeGroup)
{
    ToyItems::SampleModel model;

    auto groupItem = model.insertItem<ToyItems::ShapeGroupItem>();

    ViewLabelItem labelItem(groupItem);
    EXPECT_EQ(labelItem.data(Qt::DisplayRole).toString().toStdString(),
              ToyItems::Constants::ShapeGroupType);

    ViewDataItem dataItem(groupItem);
    EXPECT_EQ(dataItem.data(Qt::DisplayRole).value<ComboProperty>().currentIndex(), 1);
}

//! ShapeGroup item in DefaultViewModel.

TEST_F(ToyShapeGroupItemTest, inDefaultViewModelContext)
{
    ToyItems::SampleModel model;
    auto groupItem = model.insertItem<ToyItems::ShapeGroupItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    // root item should have one child, item looking at our groupItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing groupItem
    QModelIndex groupIndex = viewModel.index(0, 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(groupIndex), groupItem);
    EXPECT_EQ(viewModel.columnCount(groupIndex), 2);
    EXPECT_EQ(viewModel.rowCount(groupIndex), 3); // Cylinder, Sphere, Anysopyramid

    // setting up signal spy
    QSignalSpy spyRemove(&viewModel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyData(&viewModel, &DefaultViewModel::dataChanged);

    // changing the data
    ComboProperty combo = model.data(groupItem, ItemDataRole::DATA).value<ComboProperty>();
    combo.setCurrentIndex(0);
    model.setData(groupItem, combo.variant(), ItemDataRole::DATA);

    // expectances
    EXPECT_EQ(spyRemove.count(), 0);
    EXPECT_EQ(spyInsert.count(), 0);
    EXPECT_EQ(spyData.count(), 1);

    // what signal reports
    QList<QVariant> arguments = spyData.takeFirst();
    QModelIndex dataIndex = viewModel.index(0, 1);
    EXPECT_EQ(arguments.size(), 3); // QModelIndex left, QModelIndex right, QVector<int> roles
    EXPECT_EQ(arguments.at(0).value<QModelIndex>(), dataIndex);
    EXPECT_EQ(arguments.at(1).value<QModelIndex>(), dataIndex);
    QVector<int> expectedRoles = {Qt::DisplayRole, Qt::EditRole};
    EXPECT_EQ(arguments.at(2).value<QVector<int>>(), expectedRoles);

    // same layout
    groupIndex = viewModel.index(0, 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(groupIndex), groupItem);
    EXPECT_EQ(viewModel.columnCount(groupIndex), 2);
    EXPECT_EQ(viewModel.rowCount(groupIndex), 3); // Cylinder, Sphere, Anysopyramid
}

//! ShapeGroup item in PropertyViewModel.

TEST_F(ToyShapeGroupItemTest, inPropertyViewModelContext)
{
    ToyItems::SampleModel model;
    auto parent = model.insertItem<SessionItem>();
    parent->registerTag(TagInfo::propertyTag("property_tag", ToyItems::Constants::ShapeGroupType));

    auto groupItem = model.insertItem<ToyItems::ShapeGroupItem>(parent, "property_tag");
    ASSERT_TRUE(groupItem != nullptr);

    // constructing viewModel from sample model
    PropertyViewModel viewModel;
    viewModel.setSessionModel(&model);
    viewModel.setRootSessionItem(parent);

    // root item should have one child, item looking at our groupItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing groupItem
    QModelIndex groupIndex = viewModel.index(0, 0);
    EXPECT_EQ(viewModel.sessionItemFromIndex(groupIndex), groupItem);

    // There is only one row under groupItem, representing radius of Sphere
    EXPECT_EQ(viewModel.columnCount(groupIndex), 2);
    EXPECT_EQ(viewModel.rowCount(groupIndex), 1); // Radius of sphere

    // ViewLabelItem and ViewDataItem should look at propertyItem corresponding to sphere
    {
        QModelIndex radiusLabelIndex = viewModel.index(0, 0, groupIndex);
        QModelIndex radiusValueIndex = viewModel.index(0, 1, groupIndex);
        auto radiusLabelItem =
            dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(radiusLabelIndex));
        ASSERT_TRUE(radiusLabelItem != nullptr);
        auto radiusPropertyItem = groupItem->currentItem()->getItem(ToyItems::SphereItem::P_RADIUS);
        EXPECT_EQ(radiusLabelItem->item(), radiusPropertyItem);
        auto radiusValueItem =
            dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(radiusValueIndex));
        ASSERT_TRUE(radiusValueItem != nullptr);
        EXPECT_EQ(radiusValueItem->item(), radiusPropertyItem);
    }

    // setting up signal spy
    QSignalSpy spyRemove(&viewModel, &DefaultViewModel::rowsRemoved);
    QSignalSpy spyInsert(&viewModel, &DefaultViewModel::rowsInserted);
    QSignalSpy spyData(&viewModel, &DefaultViewModel::dataChanged);

    // changing the data (now GroupItem's current item changed from Sphere to Cylinder
    ComboProperty combo = model.data(groupItem, ItemDataRole::DATA).value<ComboProperty>();
    combo.setCurrentIndex(0);
    model.setData(groupItem, combo.variant(), ItemDataRole::DATA);

    EXPECT_EQ(viewModel.columnCount(groupIndex), 2);
    EXPECT_EQ(viewModel.rowCount(groupIndex), 2); // Radius and Height of cylinder

    // Checking ViewLabelItem and ViewDataItem corresponding to Cylinder's radius
    {
        QModelIndex radiusLabelIndex = viewModel.index(0, 0, groupIndex);
        QModelIndex radiusValueIndex = viewModel.index(0, 1, groupIndex);
        auto radiusLabelItem =
            dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(radiusLabelIndex));
        ASSERT_TRUE(radiusLabelItem != nullptr);
        auto radiusPropertyItem =
            groupItem->currentItem()->getItem(ToyItems::CylinderItem::P_RADIUS);
        EXPECT_EQ(radiusLabelItem->item(), radiusPropertyItem);
        auto radiusValueItem =
            dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(radiusValueIndex));
        ASSERT_TRUE(radiusValueItem != nullptr);
        EXPECT_EQ(radiusValueItem->item(), radiusPropertyItem);
    }

    // Checking ViewLabelItem and ViewDataItem corresponding to Cylinder's height
    {
        QModelIndex heightLabelIndex = viewModel.index(1, 0, groupIndex);
        QModelIndex heightValueIndex = viewModel.index(1, 1, groupIndex);
        auto heightLabelItem =
            dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(heightLabelIndex));
        ASSERT_TRUE(heightLabelItem != nullptr);
        auto heightPropertyItem =
            groupItem->currentItem()->getItem(ToyItems::CylinderItem::P_HEIGHT);
        EXPECT_EQ(heightLabelItem->item(), heightPropertyItem);
        auto heightValueItem =
            dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(heightValueIndex));
        ASSERT_TRUE(heightPropertyItem != nullptr);
        EXPECT_EQ(heightValueItem->item(), heightPropertyItem);
    }

    // expectances
    EXPECT_EQ(spyRemove.count(), 1);
    EXPECT_EQ(spyInsert.count(), 2);
    EXPECT_EQ(spyData.count(), 1);
}

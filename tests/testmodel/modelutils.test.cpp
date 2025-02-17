// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toy_items.h"
#include "toy_models.h"
#include <mvvm/model/modelutils.h>

using namespace ModelView;

class ModelUtilsTest : public ::testing::Test
{
public:
    ~ModelUtilsTest();
};

ModelUtilsTest::~ModelUtilsTest() = default;

TEST_F(ModelUtilsTest, topItem)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::TopItem<>(&model), nullptr);
    EXPECT_EQ(Utils::TopItem<SessionItem>(&model), nullptr);
    EXPECT_EQ(Utils::TopItem<ToyItems::MultiLayerItem>(&model), nullptr);

    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::MultiLayerItem>();

    EXPECT_EQ(Utils::TopItem<>(&model), multilayer1);
    EXPECT_EQ(Utils::TopItem<SessionItem>(&model), multilayer1);
    EXPECT_EQ(Utils::TopItem<ToyItems::MultiLayerItem>(&model), multilayer1);
}

TEST_F(ModelUtilsTest, topItems)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::TopItems<>(&model).size(), 0);
    EXPECT_EQ(Utils::TopItems<SessionItem>(&model).size(), 0);
    EXPECT_EQ(Utils::TopItems<ToyItems::MultiLayerItem>(&model).size(), 0);

    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    auto particle = model.insertItem<ToyItems::ParticleItem>();
    auto multilayer2 = model.insertItem<ToyItems::MultiLayerItem>();

    std::vector<SessionItem*> expected1 = {multilayer1, particle, multilayer2};
    EXPECT_EQ(Utils::TopItems<SessionItem>(&model), expected1);
    std::vector<ToyItems::MultiLayerItem*> expected2 = {multilayer1, multilayer2};
    EXPECT_EQ(Utils::TopItems<ToyItems::MultiLayerItem>(&model), expected2);
}

TEST_F(ModelUtilsTest, findItems)
{
    ToyItems::SampleModel model;
    EXPECT_EQ(Utils::FindItems<>(&model).size(), 1);            // because of rootItem
    EXPECT_EQ(Utils::FindItems<SessionItem>(&model).size(), 1); // because of rootItem
    EXPECT_EQ(Utils::FindItems<ToyItems::MultiLayerItem>(&model).size(), 0);

    auto multilayer1 = model.insertItem<ToyItems::MultiLayerItem>();
    model.insertItem<ToyItems::ParticleItem>();
    auto multilayer2 = model.insertItem<ToyItems::MultiLayerItem>();

    std::vector<ToyItems::MultiLayerItem*> expected2 = {multilayer1, multilayer2};
    EXPECT_EQ(Utils::FindItems<ToyItems::MultiLayerItem>(&model), expected2);

    // adding layers to multilayer
    auto layer1 = model.insertItem<ToyItems::LayerItem>(multilayer1);
    auto layer2 = model.insertItem<ToyItems::LayerItem>(multilayer2);

    std::vector<ToyItems::LayerItem*> expected3 = {layer1, layer2};
    EXPECT_EQ(Utils::FindItems<ToyItems::LayerItem>(&model), expected3);
}

TEST_F(ModelUtilsTest, DeleteItemFromModel)
{
    ToyItems::SampleModel model;

    auto item = model.insertItem<SessionItem>();
    EXPECT_EQ(model.rootItem()->childrenCount(), 1);
    Utils::DeleteItemFromModel(item);
    EXPECT_EQ(model.rootItem()->childrenCount(), 0);
}

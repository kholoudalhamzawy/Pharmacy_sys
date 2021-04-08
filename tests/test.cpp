#include "gtest/gtest.h"
#include "pharma.h"


class PharmaTest : public ::testing::Test{
protected:
    void SetUp() override{
        pharmacy.add_med("alex",2,3);
    }
    med_manager pharmacy;
};

TEST_F(PharmaTest,InsertMed){
    ASSERT_EQ(pharmacy.get_meds_num(),1);
}
TEST_F(PharmaTest,ValidId){
    ASSERT_NE(pharmacy.valid_id(2), false);
}
TEST_F(PharmaTest,DeleteMed){
    pharmacy.delete_med(2);
    ASSERT_EQ(pharmacy.get_meds_num(),0);
}
TEST_F(PharmaTest,UpdatePrice){
    pharmacy.update_price(2,6);
    EXPECT_EQ(pharmacy.get_med(2)->get_price(),6);
}
TEST_F(PharmaTest,ChangePreservationBehavior){
    ASSERT_EQ(pharmacy.change_preservation_behavior(2,make_unique<Cold_preservation>()),1);
}
TEST_F(PharmaTest,ChangeDosageBehavior){
    ASSERT_EQ(pharmacy.change_dosage_behavior(2,make_unique<Inject_dosage>()),1);
}




int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
    return 0;
}
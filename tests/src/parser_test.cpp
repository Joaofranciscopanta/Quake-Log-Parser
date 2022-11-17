#include "gtest/gtest.h"
#include "../../src/include/myparser.h"

TEST(ParsingTest, NameDetecTEST_I){
    char** word = (char **) "21:42 Kill: 1022 2 22: <world> killed Isgalamido by MOD_TRIGGER_HURT\n";
    string killer = detectKiller(word);
    cout << killer;
}
int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}



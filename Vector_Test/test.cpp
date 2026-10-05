#include "pch.h"

#define VECTOR_TESTS
//#define MATH_VECTOR_TESTS

#ifdef VECTOR_TESTS
#include "vector.h"

TEST(ClassVector, can_create_with_default_constructor) {
    Vector<double> V1;
    EXPECT_EQ(V1.getSize(), 0);
    EXPECT_EQ(V1.getCapacity(), 16);
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector<double> V1(10);
    Vector<double> V2(0);
    Vector<double> V3(1000);

    EXPECT_EQ(V1.getSize(), 10);
    EXPECT_EQ(V1.getCapacity(), 32);
    EXPECT_EQ(V2.getSize(), 0);
    EXPECT_EQ(V2.getCapacity(), 16);
    EXPECT_EQ(V3.getSize(), 1000);
    EXPECT_EQ(V3.getCapacity(), 1024);
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    Vector<double> V2({});
    double example1[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    EXPECT_EQ(V1.getSize(), 16);
    EXPECT_EQ(V1.getCapacity(), 32);
    EXPECT_EQ(V2.getSize(), 0);
    EXPECT_EQ(V2.getCapacity(), 16);
    for (size_t i = 0; i < V1.getSize(); i++) {
        EXPECT_EQ(V1[i], example1[i]);
    }
}

TEST(ClassVector, can_create_with_init_constructor) {
    double* list1 = new double[16];
    for (int i = 0; i < 16; i++) {
        list1[i] = i;
    }
    Vector<double> V1(16, list1);

    EXPECT_EQ(V1.getSize(), 16);
    EXPECT_EQ(V1.getCapacity(), 32);
    for (size_t i = 0; i < V1.getSize(); i++) {
        EXPECT_EQ(V1[i], list1[i]);
    }
    delete[] list1;
}

TEST(ClassVector, can_create_with_copy_constructor) {
    Vector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    Vector<double> V2(V1);
    double example1[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    EXPECT_EQ(V1.getSize(), V2.getSize());
    EXPECT_EQ(V1.getCapacity(), V2.getCapacity());
    for (size_t i = 0; i < V1.getSize(); i++) {
        EXPECT_EQ(V1[i], example1[i]);
        EXPECT_EQ(V2[i], example1[i]);
    }
}

TEST(ClassVector, can_create_with_move_constructor) {
    Vector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    Vector<double> V3 = V1;
    EXPECT_TRUE(V3 == V1);
    Vector<double> V2(std::move(V1));
    EXPECT_TRUE(V3 == V2);
}

TEST(ClassVector, can_isEmpty) {
    Vector<double> V1;
    Vector<double> V2(0);
    Vector<double> V4({ 1,2,3 });
    Vector<double> V5({ 1,2,3,0 });

    EXPECT_TRUE(V1.isEmpty());
    EXPECT_TRUE(V2.isEmpty());
    EXPECT_FALSE(V4.isEmpty());
    EXPECT_FALSE(V5.isEmpty());
}

TEST(ClassVector, can_get_front) {
    Vector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    Vector<double> V2({ 1000,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    EXPECT_DOUBLE_EQ(V1[0], 1);
    EXPECT_DOUBLE_EQ(V2[0], 1000);
}

TEST(ClassVector, can_get_back) {
    Vector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    Vector<double> V2({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,19000 });
    EXPECT_DOUBLE_EQ(V1[V1.getSize() - 1], 16);
    EXPECT_DOUBLE_EQ(V2[V2.getSize() - 1], 19000);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    Vector<double> V1;
    ASSERT_THROW(V1[0], std::logic_error);
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    Vector<double> V1;
    ASSERT_THROW(V1[V1.getSize()], std::logic_error);
}

TEST(ClassVector, can_output_with_operator_cout) {
    Vector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    Vector<double> vec;
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());

    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_pushFront) {
    Vector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    for (size_t i = 0; i < 4; i++) {
        vec.pushFront(3.0 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    EXPECT_EQ(8, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushFrontMany) {
    Vector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    double list[4] = { 0,1,2,3 };
    vec.pushFrontMany(list, 4);
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    EXPECT_EQ(8, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushFront_in_empty_vector) {
    Vector<double> vec;
    std::stringstream out;
    EXPECT_EQ(0, vec.getSize());
    EXPECT_EQ(16, vec.getCapacity());
    for (size_t i = 0; i < 4; i++) {
        vec.pushFront(3.0 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushFrontMany_in_empty_vector) {
    Vector<double> vec;
    std::stringstream out;
    double list[4] = { 0,1,2,3 };
    vec.pushFrontMany(list, 4);
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushFront_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
    for (size_t i = 0; i < 3; i++) {
        vec.pushFront(3.0 - i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(17, vec.getSize());
    EXPECT_EQ(48, vec.getCapacity());
}

TEST(ClassVector, can_pushFrontMany_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
    double list[3] = { 1,2,3 };
    vec.pushFrontMany(list, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(17, vec.getSize());
    EXPECT_EQ(48, vec.getCapacity());
}

TEST(ClassVector, can_pushBack) {
    Vector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    for (size_t i = 0; i < 4; i++) {
        vec.pushBack(3.0 - i);
    }
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8, 3, 2, 1, 0 }", out.str());
    EXPECT_EQ(8, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushBackMany) {
    Vector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    double list[4] = { 0,1,2,3 };
    vec.pushBackMany(list, 4);
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8, 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(8, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushBack_in_empty_vector) {
    Vector<double> vec;
    std::stringstream out;
    for (size_t i = 0; i < 4; i++) {
        vec.pushBack(3.0 - i);
    }
    out << vec;
    EXPECT_EQ("{ 3, 2, 1, 0 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushBackMany_in_empty_vector) {
    Vector<double> vec;
    std::stringstream out;
    double list[4] = { 0,1,2,3 };
    vec.pushBackMany(list, 4);
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
}

TEST(ClassVector, can_pushBack_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(32, vec.getCapacity());
    for (size_t i = 0; i < 3; i++) {
        vec.pushBack(15.0 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 }", out.str());
    EXPECT_EQ(17, vec.getSize());
    EXPECT_EQ(48, vec.getCapacity());
}


TEST(ClassVector, can_pushBackMany_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    double list[3] = { 3,2,1 };
    vec.pushBackMany(list, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 3, 2, 1 }", out.str());
    EXPECT_EQ(17, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
}

TEST(ClassVector, can_insert) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.insert(99, 2);
    out << vec;
    EXPECT_EQ("{ 1, 2, 99, 3, 4, 5 }", out.str());
    EXPECT_EQ(6, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_insertMany) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    double list[3] = { 99, 100, 101 };
    vec.insertMany(list, 3, 2);
    out << vec;
    EXPECT_EQ("{ 1, 2, 99, 100, 101, 3, 4, 5 }", out.str());
    EXPECT_EQ(8, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_insert_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    vec.insert(99, 7);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 99, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(15, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
}

TEST(ClassVector, can_insertMany_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    double list[3] = { 99, 100, 101 };
    vec.insertMany(list, 3, 7);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 99, 100, 101, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(17, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
}

TEST(ClassVector, can_insert_to_front) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.insert(99, 0);
    out << vec;
    EXPECT_EQ("{ 99, 1, 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(6, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_insertMany_to_front) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    double list[3] = { 99, 100, 101 };
    vec.insertMany(list, 3, 0);
    out << vec;
    EXPECT_EQ("{ 99, 100, 101, 1, 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(8, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector<double> vec({ 1,2,3,4,5 });
    EXPECT_THROW(vec.insert(99, 10), std::out_of_range);
    EXPECT_THROW(vec.insertMany(nullptr, 3, 10), std::out_of_range);
}

TEST(ClassVector, can_popFront) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.popFront();
    out << vec;
    EXPECT_EQ("{ 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_popFrontMany) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.popFrontMany(3);
    out << vec;
    EXPECT_EQ("{ 4, 5 }", out.str());
    EXPECT_EQ(2, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_popFront_with_reallocation) {
    Vector<double> vec({ 99,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
    vec.popFront();
    out << vec;
    EXPECT_EQ("{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_popFrontMany_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
    vec.popFrontMany(3);
    out << vec;
    EXPECT_EQ("{ 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
    EXPECT_EQ(12, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, throw_when_try_popFront_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.popFront(), std::logic_error);
}

TEST(ClassVector, throw_when_try_popFrontMany_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.popFrontMany(3), std::logic_error);
}

TEST(ClassVector, can_popBack) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.popBack();
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_popBackMany) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.popBackMany(3);
    out << vec;
    EXPECT_EQ("{ 1, 2 }", out.str());
    EXPECT_EQ(2, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_popBack_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
    vec.popBack();
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_popBackMany_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    std::stringstream out;
    EXPECT_EQ(16, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
    vec.popBackMany(5);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    EXPECT_EQ(11, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, throw_when_try_popBack_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.popBack(), std::logic_error);
}

TEST(ClassVector, throw_when_try_popBackMany_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.popBackMany(3), std::logic_error);
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 14; i++) {
        vec.pushBack(i + 1);
    }

    vec.popFront();
    vec.pushBack(15);

    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    EXPECT_DOUBLE_EQ(15.0, vec[vec.getSize()-1]);

    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }

    vec.popBack();

    EXPECT_EQ(13, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    EXPECT_DOUBLE_EQ(14.0, vec[vec.getSize()-1]);

    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector<double> vec;

    for (size_t i = 0; i < 14; i++) {
        vec.pushBack(i + 1);
    }

    vec.popBack();
    vec.pushFront(0);

    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    EXPECT_DOUBLE_EQ(0.0, vec[0]);

    for (size_t i = 0; i < vec.getSize() - 1; i++) {
        EXPECT_DOUBLE_EQ(vec[i + 1], i + 1);
    }

    vec.popFront();

    EXPECT_EQ(13, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
    EXPECT_DOUBLE_EQ(1.0, vec[0]);

    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_erase) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.erase(2);
    out << vec;
    EXPECT_EQ("{ 1, 2, 4, 5 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_eraseMany) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8 });
    std::stringstream out;
    vec.eraseMany(2, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 6, 7, 8 }", out.str());
    EXPECT_EQ(5, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_erase_front) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_erase_back) {
    Vector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.erase(4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4 }", out.str());
    EXPECT_EQ(4, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_erase_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
    vec.erase(5);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
    EXPECT_EQ(14, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, can_eraseMany_with_reallocation) {
    Vector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    std::stringstream out;
    EXPECT_EQ(16, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());
    vec.eraseMany(5, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    EXPECT_EQ(13, vec.getSize());
    EXPECT_EQ(15, vec.getCapacity());
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.erase(0), std::logic_error);
}

TEST(ClassVector, throw_when_try_eraseMany_from_empty_vector) {
    Vector<double> vec;
    EXPECT_THROW(vec.eraseMany(0, 3), std::logic_error);
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector<double> vec({ 1,2,3,4,5 });
    EXPECT_THROW(vec.erase(10), std::out_of_range);
}

TEST(ClassVector, throw_when_try_eraseMany_with_wrong_count) {
    Vector<double> vec({ 1,2,3,4,5 });
    EXPECT_THROW(vec.eraseMany(10, 2), std::logic_error);
    EXPECT_THROW(vec.eraseMany(2, 10), std::logic_error);
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector<double> vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.popFront();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.pushFront(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.popBack();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.pushBack(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.pushBack(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.getSize());
    EXPECT_EQ(30, vec.getCapacity());

    for (size_t i = 0; i < vec.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_assigment) {
    Vector<double> vec_1{ 1,2,3,4 };
    Vector<double> vec_2;

    vec_2 = vec_1;

    EXPECT_EQ(4, vec_1.getSize());
    EXPECT_EQ(15, vec_1.getCapacity());
    EXPECT_EQ(4, vec_2.getSize());
    EXPECT_EQ(15, vec_2.getCapacity());

    for (size_t i = 0; i < vec_2.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec_1[i], vec_2[i]);
        EXPECT_DOUBLE_EQ(vec_2[i], i + 1);
    }

    vec_1.popBack();
    EXPECT_EQ(3, vec_1.getSize());
    EXPECT_EQ(4, vec_2.getSize());
}

TEST(ClassVector, can_move_assigment) {
    Vector<double> vec_1;
    Vector<double> vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.pushBack(5 + i);
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.pushFront(4 - i);
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.getSize());
    EXPECT_EQ(0, vec_1.getCapacity());

    EXPECT_EQ(8, vec_2.getSize());
    EXPECT_EQ(15, vec_2.getCapacity());

    for (size_t i = 0; i < vec_2.getSize(); i++) {
        EXPECT_DOUBLE_EQ(vec_2[i], i + 1);
    }
}

#endif

#ifdef MATH_VECTOR_TESTS
#include "mathvector.h"
TEST(ClassMathVector, can_create_with_default_constructor) {
    EXPECT_EQ(1, 1);
}
#endif
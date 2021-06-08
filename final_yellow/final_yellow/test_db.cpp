//
//  test_db.cpp
//  test
//
//  Created by Andre on 30/12/20.
//

#include "test_db.h"

void TestAddEntry() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        std::ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
    }
    
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        std::ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "only unique");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "first day of the year");
        std::ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 first day of the year\n", out.str(), "several in one day");
    }
    {
        Database db;
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        std::ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse added");
    }
}

void TestInsertionOrder()
{
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "party");
        db.Add({2017, 1, 7}, "pie");
        std::ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2017-01-07 party\n2017-01-07 pie\n", out.str(), "Remove by date, left");
    }
}

void TestLast() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "party");
        db.Add({2017, 1, 7}, "pie");
        auto answer = std::make_pair(Date(2017, 1, 7), "pie");
        AssertEqual(db.Last({2017, 1, 8}), answer, "last from added");
        AssertEqual(db.Last({2018, 1, 8}), answer, "last from added");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestAddEntry, "TestAddEntry");
    tr.RunTest(TestInsertionOrder, "TestInsertationOrder");
    tr.RunTest(TestLast, "TestLast");
}

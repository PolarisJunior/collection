
#pragma once
#include <memory>
#include <optional>
#include <string>

// std::optional<RelationalDatabase> db =
//   RelationalDatabase::loadDatabase("test2.db");
// if (db) {
//   printf("create\n");
//   db->createTable();
// } else {
//   printf("not create\n");
// }

struct sqlite3;

class RelationalDatabase {
 public:
  ~RelationalDatabase();
  explicit RelationalDatabase(sqlite3** sql);

  static std::optional<RelationalDatabase> loadDatabase(
      const std::string& dbName);

  bool createTable();
  bool exec();

 private:
  sqlite3* db;
  bool valid;
};
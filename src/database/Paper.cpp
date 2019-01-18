#include "Paper.h"
using namespace std;
Paper::Paper(string tit, string a, string top, int d, int id) {
    this->author = a;
    this->id = id;
    this->date = d;
    this->title = tit;
    string identifier = to_string(id);
    this->entity = azure::storage::table_entity(utility::conversions::to_string_t(identifier), 0);
    azure::storage::table_entity::properties_type &properties = this->entity.properties();
    properties.reserve(3);
    properties[_XPLATSTR("Date")] = azure::storage::entity_property(this->date);
    properties[_XPLATSTR("Author")] =
        azure::storage::entity_property(utility::conversions::to_string_t(this->author));
    properties[_XPLATSTR("Title")] =
        azure::storage::entity_property(utility::conversions::to_string_t(this->title));
}

Paper::Paper(vector<string> line) {
    this->id = stoi(line[0]);
    cout << this->id << endl;
    this->author = "n/a";
    this->title = line[5];
    int d = stoi(line[8]);
    this->date = d;
    string identifier = to_string(this->id);
    this->entity =
        azure::storage::table_entity(utility::conversions::to_string_t(identifier), _XPLATSTR("0"));
    azure::storage::table_entity::properties_type &properties = this->entity.properties();
    properties.reserve(3);
    properties[_XPLATSTR("Date")] = azure::storage::entity_property(this->date);
    properties[_XPLATSTR("Author")] =
        azure::storage::entity_property(utility::conversions::to_string_t(this->author));
    properties[_XPLATSTR("Title")] =
        azure::storage::entity_property(utility::conversions::to_string_t(this->title));
}

azure::storage::table_result Paper::upload(azure::storage::cloud_table &table) {
    table.create_if_not_exists();
    azure::storage::table_operation insert_paper =
        azure::storage::table_operation::insert_entity(this->entity);
    return table.execute(insert_paper);
}
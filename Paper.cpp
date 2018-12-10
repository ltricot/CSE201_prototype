#include "Paper.h"

Paper::Paper(string tit, string a, string top, int d, int id) {
	this->author = a;
	this->id = id;
	this->date = d;
	this->title = tit;
	this->topic = top;
	int decadeint;
	decadeint = d / 10;
	decadeint *= 10;
	string decade = to_string(decadeint);
	this->entity = azure::storage::table_entity(utility::conversions::to_string_t(decade), utility::conversions::to_string_t(title));
	azure::storage::table_entity::properties_type& properties = this->entity.properties();
	properties.reserve(3);
	properties[_XPLATSTR("Date")] = azure::storage::entity_property(this->date);
	properties[_XPLATSTR("Author")] = azure::storage::entity_property(utility::conversions::to_string_t(this->author));
	properties[_XPLATSTR("ID")] = azure::storage::entity_property(this->id);
}
azure::storage::table_result Paper::upload(azure::storage::cloud_table& table) {
	table.create_if_not_exists();
	azure::storage::table_operation insert_paper = azure::storage::table_operation::insert_entity(this->entity);
	return table.execute(insert_paper);
}
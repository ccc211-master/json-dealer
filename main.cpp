#include <iostream>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"

using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using nlohmann::json;


/*
{
  "fields": [
    {"name": "id", "type": "int", "length": 4},
    {"name": "name", "type": "char", "length": 20},
    {"name": "age", "type": "int", "length": 4},
    {"name": "sex", "type": "char", "length": 1},
    {"name": "city", "type": "char", "length": 20}
  ], 
  "primary-key": "id",
  "secondary-key": ["sex", "city"]
}
*/


int main(int argc, char* argv[]){
    stringstream s("{\"name\":\"John\",\"age\":12}");
    json data = json::parse(s);
    cout << data << endl;
    cout << data["name"] << endl;
    cout << data["age"] << endl;
    auto a = data["age"].template get<int>();
    data["age"] = a + 1;
    cout << data << endl;
    cout << endl << endl << endl;
    json fileDescription = R"(
        {
        "fields": [
            {"name": "id", "type": "int", "length": 4},
            {"name": "name", "type": "char", "length": 20},
            {"name": "age", "type": "int", "length": 4},
            {"name": "sex", "type": "char", "length": 1},
            {"name": "city", "type": "char", "length": 20}
        ], 
        "primary-key": "id",
        "secondary-key": ["sex", "city"]
        }    
    )"_json;

    cout << "Number of fields: " << fileDescription["fields"].size() << endl;

    cout << "File Fields Description:" << endl;
    int recordSize = 0;
    for (auto& element: fileDescription["fields"]){
        cout << element["name"] << "\t" << element["type"] << "\t" << element["length"] << endl;
        recordSize += element["length"].template get<int>();
    }
    cout << "The record length is: " << recordSize << endl;
    cout << "Primary Key is: " << fileDescription["primary-key"] << endl;
    cout << "Secondary Keys are: " << endl;
    for (auto& sk: fileDescription["secondary-key"])
        cout << sk << endl;


    return 0;
}
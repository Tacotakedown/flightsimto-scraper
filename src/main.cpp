#include <iostream>
#include <fstream>
#include <regex>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;


struct ScrapedData {
    uint64_t downloads;
    utility::string_t last_checked;
};


pplx::task<void> scrape_and_write_to_json(const utility::string_t& link) {
    http_client client(link);

    return client.request(methods::GET)
    .then([](http_response response) {
        if(response.status_code() == status_codes::OK) {
            auto stream = response.body();
            concurrency::streams::container_buffer<std::string> buffer;
            
            return stream.read_to_end(buffer).then([buffer](size_t bytesRead) {
                std::wstring html = utility::conversions::to_utf16string(buffer.collection());
                std::wregex regex(U(R"((\d+)K Downloads)"));
                std::wsmatch matches;
                if (std::regex_search(html, matches, regex)) {
                    uint64_t downloads = std::stoull(matches[1].str()) * 1000;
                    ScrapedData data;
                    data.downloads = downloads;
                    data.last_checked = utility::datetime::utc_now().to_string(utility::datetime::ISO_8601);

                    web::json::value json_data;
                    json_data[U("downloads")] = web::json::value::number(data.downloads);
                    json_data[U("Last Checked")] = web::json::value::string(data.last_checked);

                    std::wcout << json_data.serialize() << std::endl;
                } else {
                    std::wcout << "Downloads not found in HTML." << std::endl;
                }
            });
        } else {
            throw std::runtime_error("Failed to fetch HTML");
        }
    });
}


int main(int argc, char* argv[]) {
    if (argc != 2){
        std::cerr << "Usage: " << argv[0] << " --link=\"https://flightsim.to/file/12408/msfs-native-c-17-globemaster\"" << std::endl;
        return 1;
    }

    std::string arg = argv[1];
    std::smatch match;
    std::regex regex(R"--(--link=(https:\/\/flightsim\.to\/file\/[^"]+))--");
    if (std::regex_match(arg,match,regex)) {
        utility::string_t link = utility::conversions::to_utf16string(match[1].str());
        scrape_and_write_to_json(link).wait();
    }else {
        std::cerr << "Invalid link. Only flightsim.to is supported" << std::endl;
        return 1;
    }


    system("PAUSE");
    return 0;
}
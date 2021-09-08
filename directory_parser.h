#pragma once

#include <filesystem>
#include <vector>
#include <string>

class directory_parser
{
public:
    directory_parser() = default;
    explicit directory_parser(std::filesystem::path);
    void set_path(const std::filesystem::path&);
    void add_filters(const std::vector<std::string>&);
    void scan_folder();
    void delete_scanned_files();
    static void delete_scanned_files(std::vector<std::filesystem::path>&);
    [[nodiscard]] const std::vector<std::filesystem::path>& scan_results() const;
    double get_files_size() const;
private:
    std::filesystem::path m_folder_path;
    std::vector<std::filesystem::path> m_scanned_files{};
    std::vector<std::string> m_filtered_types{};

    double m_size{ 0 };

    static bool is_optional(const std::filesystem::path&, const std::vector<std::string>&);
};

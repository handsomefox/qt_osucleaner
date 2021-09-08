#include "directory_parser.h"
#include <iostream>

directory_parser::directory_parser(std::filesystem::path folder_path)
    : m_folder_path(std::move(folder_path))
{
    if (m_folder_path.empty())
        throw std::exception("[ERROR] Specified path is empty.\n");

    if (!is_directory(m_folder_path))
        throw std::exception("[ERROR] Specified path is not a directory.\n");
}

void directory_parser::set_path(const std::filesystem::path & new_path)
{
    m_folder_path = new_path;

    if (m_folder_path.empty())
        throw std::exception("[ERROR] Specified path is empty.\n");

    if (!is_directory(m_folder_path))
        throw std::exception("[ERROR] Specified path is not a directory.\n");
}

void directory_parser::add_filters(const std::vector<std::string>& list_of_extensions)
{
    for (const auto& filter : list_of_extensions)
        m_filtered_types.push_back(filter);
}

void directory_parser::scan_folder()
{
    using iterator = std::filesystem::recursive_directory_iterator;

    for (const auto& entry : iterator(m_folder_path))
    {
        if (entry.is_regular_file())
            if (is_optional(entry.path(), m_filtered_types))
            {
                m_size += static_cast<double>(entry.file_size()) / 10e6;
                m_scanned_files.push_back(entry);
            }
    }
}

void directory_parser::delete_scanned_files()
{
    for (auto& file : m_scanned_files)
    {
        std::cout << "[EVENT] Removing " << file << '\n';
        remove(file);
    }
    m_scanned_files.clear();
}

void directory_parser::delete_scanned_files(std::vector<std::filesystem::path>& scanned_files)
{
    for (auto& file : scanned_files)
    {
        std::cout << "[EVENT] Removing " << file << '\n';
        remove(file);
    }
    scanned_files.clear();
}

const std::vector<std::filesystem::path>& directory_parser::scan_results() const
{
    return m_scanned_files;
}

double directory_parser::get_files_size() const
{
    return m_size;
}

bool directory_parser::is_optional(const std::filesystem::path& file, const std::vector<std::string>& filter_list)
{
    for (auto& filter : filter_list)
        if (file.has_extension())
            if (file.extension() == filter) return true;

    return false;
}

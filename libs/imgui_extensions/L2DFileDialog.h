/*
	Copyright 2020 Limeoats

   	Licensed under the Apache License, Version 2.0 (the "License");
   	you may not use this file except in compliance with the License.
   	You may obtain a copy of the License at
	
       	http://www.apache.org/licenses/LICENSE-2.0
	
   	Unless required by applicable law or agreed to in writing, software
   	distributed under the License is distributed on an "AS IS" BASIS,
   	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   	See the License for the specific language governing permissions and
   	limitations under the License.
*/

#pragma once


#include <imgui.h>
#include <imgui_internal.h>
#include <chrono>
#include <string>
#include <time.h>
#include <filesystem>
#include <sstream>

using namespace std::chrono_literals;

namespace FileDialog {

	enum class FileDialogType {
		OpenFile,
		SelectFolder
	};
	enum class FileDialogSortOrder {
		Up,
		Down,
		None
	};

	enum class Result
	{
		None,
		Confirm,
		Cancel
	};

	Result ShowFileDialog(bool& open, char* buffer, const char* extension = "", FileDialogType type = FileDialogType::OpenFile) 
	{
		static int file_dialog_file_select_index = 0;
		static int file_dialog_folder_select_index = 0;
		static std::string file_dialog_current_path = std::filesystem::current_path().string();
		static std::string file_dialog_current_file = "";
		static std::string file_dialog_current_folder = "";
		static char file_dialog_error[500] = "";
		
		std::string extension_filter = extension;
		static bool initial_path_set = false;
		
		Result result = Result::None;
		if (open) {
			// Check if there was already something in the buffer. If so, try to use that path (if it exists).
			// If it doesn't exist, just put them into the current path.
			if (!initial_path_set && strlen(buffer) > 0) {
				auto path = std::filesystem::path(buffer);
				if (std::filesystem::is_directory(path)) {
					file_dialog_current_path = buffer;
				}
				else {
					// Check if this is just a file in a real path. If so, use the real path.
					// If that still doesn't work, use current path.
					if (std::filesystem::exists(path)) {
						// It's a file! Take the path and set it.
						file_dialog_current_path = path.remove_filename().string();
					}
					else {
						// An invalid path was entered
						file_dialog_current_path = std::filesystem::current_path().string();
					}
				}
				initial_path_set = true;
			}

			const char* window_title = (type == FileDialogType::OpenFile ? "Select a file" : "Select a folder");
			ImGui::Begin(window_title);

			std::vector<std::filesystem::directory_entry> files;
			std::vector<std::filesystem::directory_entry> folders;

			try {
				for (auto& p : std::filesystem::directory_iterator(file_dialog_current_path)) {
					if (p.is_directory()) {
						folders.push_back(p);
					}
					else {
						// If we have an extension filter, filter off non-extension files
						if(extension_filter.empty() || 
						   (p.path().extension().string() == extension_filter)) 
						{
							files.push_back(p);
						}
					}
				}
			}
			catch (...) {}

			ImGui::Text("%s", file_dialog_current_path.c_str());

			// Render directory panel
			ImVec2 contentAvailable = ImGui::GetContentRegionAvail();
			float availableX = contentAvailable.x * 0.98;
			float tableHeight = contentAvailable.y * 0.85;
			auto directoryDimensions = ImVec2(availableX * 0.2, tableHeight);
			auto fileDimensions = ImVec2(availableX * 0.8, tableHeight);
		
			// Directoryes
			ImGui::BeginChild("Directories##1", directoryDimensions, true, ImGuiWindowFlags_HorizontalScrollbar);
			if (ImGui::Selectable("..", false, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					file_dialog_current_path = std::filesystem::path(file_dialog_current_path).parent_path().string();
				}
			}
			for (int i = 0; i < folders.size(); ++i) {
				if (ImGui::Selectable(folders[i].path().stem().string().c_str(), i == file_dialog_folder_select_index, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
					file_dialog_current_file = "";
					if (ImGui::IsMouseDoubleClicked(0)) {
						file_dialog_current_path = folders[i].path().string();
						file_dialog_folder_select_index = 0;
						file_dialog_file_select_index = 0;
						ImGui::SetScrollHereY(0.0f);
						file_dialog_current_folder = "";
					}
					else {
						file_dialog_folder_select_index = i;
						file_dialog_current_folder = folders[i].path().stem().string();
					}
				}
			}
			ImGui::EndChild();

			ImGui::SameLine();

			// File table information
			ImGui::BeginChild("Files##1", fileDimensions, true, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::Columns(4);
			static  float initial_column_spacings[3] = { 400.0f, 80.0f, 80.0f };
			for(int i = 0; i < 3; i++)
			{
				if(initial_column_spacings[i] != 0.0f)
				{
					ImGui::SetColumnWidth(i, initial_column_spacings[i]);
					initial_column_spacings[i] = 0.0f;
				}
			}

			enum class SortType { File, Size, Type, Date, MAX, };
			static const char* SORT_STRINGS[] { "File", "Size", "Type", "Date", };

			static FileDialogSortOrder sort_order = FileDialogSortOrder::None;
			static SortType sort_type;

			for(int i = 0; i < static_cast<int>(SortType::MAX); i++)
			{
				if(ImGui::Selectable(SORT_STRINGS[i]))
				{
					sort_order = sort_type == static_cast<SortType>(i) ? 
						FileDialogSortOrder::Down : 
						FileDialogSortOrder::Up;
					sort_type = static_cast<SortType>(i);
				}
				ImGui::NextColumn();
			}

			ImGui::Separator();

			// Sort files
			if(sort_order != FileDialogSortOrder::None)
			{
				std::sort(files.begin(), files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
					bool value;
					switch(sort_type)
					{
						case SortType::File: value = a.path().filename().string() > b.path().filename().string(); break;
						case SortType::Size: value = a.file_size() > b.file_size(); break;
						case SortType::Type: value = a.path().extension().string() > b.path().extension().string(); break;
						case SortType::Date: value = a.last_write_time() > b.last_write_time(); break;
						default: value = true; break;
					};
					if(sort_order == FileDialogSortOrder::Up)
					{
						value = !value;
					}
					return value;
				});
			}

			// Populate file data
			for (int i = 0; i < files.size(); ++i) {
				if (ImGui::Selectable(files[i].path().filename().string().c_str(), i == file_dialog_file_select_index, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
					file_dialog_file_select_index = i;
					file_dialog_current_file = files[i].path().filename().string();
					file_dialog_current_folder = "";
				}
				ImGui::NextColumn();
				ImGui::TextUnformatted(std::to_string(files[i].file_size()).c_str());
				ImGui::NextColumn();
				ImGui::TextUnformatted(files[i].path().extension().string().c_str());
				ImGui::NextColumn();
				auto ftime = files[i].last_write_time();
				auto st = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now());
				std::time_t tt = std::chrono::system_clock::to_time_t(st);

				std::tm mt;
				localtime_s(&mt, &tt);
				std::stringstream ss;
				ss << std::put_time(&mt, "%F %R");
				
				ImGui::TextUnformatted(ss.str().c_str());
				ImGui::NextColumn();
			}
			ImGui::EndChild();

			std::string selected_file_path = file_dialog_current_path + (file_dialog_current_path.back() == '\\' ? "" : "\\") + (file_dialog_current_folder.size() > 0 ? file_dialog_current_folder : file_dialog_current_file);
			ImGui::PushItemWidth(availableX);
			ImGui::Text(selected_file_path.data());

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);
			
			static auto reset_everything = [&]() {
				file_dialog_file_select_index = 0;
				file_dialog_folder_select_index = 0;
				file_dialog_current_file = "";
				strcpy_s(file_dialog_error, "");
				initial_path_set = false;
			};
			
			ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 220);
			if (ImGui::Button("Cancel")) {
				result = Result::Cancel;
				open = false;
				reset_everything();
			}
			ImGui::SameLine();
			if (ImGui::Button("Choose")) {
				if (type == FileDialogType::SelectFolder) {
					if (file_dialog_current_folder == "") {
						strcpy_s(file_dialog_error, "Error: You must select a folder!");
					}
					else {
						auto path = file_dialog_current_path + (file_dialog_current_path.back() == '\\' ? "" : "\\") + file_dialog_current_file;
						strcpy_s(buffer, path.length() + 1, path.c_str());
						strcpy_s(file_dialog_error, "");
						result = Result::Confirm;
						open = false;
						reset_everything();
					}
				}
				else if (type == FileDialogType::OpenFile) {
					if (file_dialog_current_file == "") {
						strcpy_s(file_dialog_error, "Error: You must select a file!");
					}
					else {
						auto path = file_dialog_current_path + (file_dialog_current_path.back() == '\\' ? "" : "\\") + file_dialog_current_file;
						strcpy_s(buffer, path.length() + 1, path.c_str());
						strcpy_s(file_dialog_error, "");
						result = Result::Confirm;
						open = false;
						reset_everything();
					}
				}
			}

			if (strlen(file_dialog_error) > 0) {
				ImGui::TextColored(ImColor(1.0f, 0.0f, 0.2f, 1.0f), file_dialog_error);
			}

			ImGui::End();
		}
		return result;
	}
}
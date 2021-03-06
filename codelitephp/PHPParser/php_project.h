#ifndef PHP_PROJECT_H
#define PHP_PROJECT_H

#include <map>
#include <vector>
#include <set>
#include "php_project_settings_data.h"
#include <wx/sharedptr.h>
#include <wx/progdlg.h>

class PHPProject
{
    wxString m_name;
    bool m_isActive;
    PHPProjectSettingsData m_settings;
    wxFileName m_filename;
    wxString m_importFileSpec;
    wxArrayString m_files;
    wxString m_excludeFolders;

public:
    typedef wxSharedPtr<PHPProject> Ptr_t;
    typedef std::map<wxString, PHPProject::Ptr_t> Map_t;

    /**
     * @class CreateData
     */
    struct CreateData
    {
        wxString path;
        wxString name;
        wxString phpExe;
        int projectType;
        bool importFilesUnderPath;
        wxString ccPaths;
        
        CreateData()
            : projectType(0)
            , importFilesUnderPath(false)
        {
        }
    };

public:
    PHPProject()
        : m_isActive(false)
        , m_importFileSpec(
              "*.php;*.inc;*.phtml;*.js;*.html;*.css;*.scss;*.json;*.xml;*.ini;*.md;*.txt;*.text;.htaccess")
        , m_excludeFolders(".git;.svn;.codelite;.clang")
    {
    }
    ~PHPProject() {}

    void Create(const wxFileName& filename, const wxString& name);
    void Load(const wxFileName& filename);
    void Save();

    void SetExcludeFolders(const wxString& excludeFolders) { this->m_excludeFolders = excludeFolders; }
    const wxString& GetExcludeFolders() const { return m_excludeFolders; }
    const wxString& GetImportFileSpec() const { return m_importFileSpec; }
    void SetFilename(const wxFileName& filename) { this->m_filename = filename; }
    const wxFileName& GetFilename() const { return m_filename; }
    void SetSettings(const PHPProjectSettingsData& settings) { this->m_settings = settings; }
    const PHPProjectSettingsData& GetSettings() const { return m_settings; }
    PHPProjectSettingsData& GetSettings() { return m_settings; }

    void ToJSON(JSONElement& element) const;
    void FromJSON(const JSONElement& element);

    bool IsOk() const { return !m_name.IsEmpty(); }
    bool IsActive() const { return m_isActive; }
    void SetIsActive(bool isActive) { this->m_isActive = isActive; }
    /**
     * @brief return a list of all project files (fullpath)
     */
    wxArrayString& GetFiles(wxProgressDialog* progress);
    
    /**
     * @brief return a list of all project files (fullpath)
     */
    void GetFilesArray(wxArrayString& files) const;
    
    /**
     * @brief check if filename is part of this project
     * @param filename
     */
    bool HasFile(const wxFileName& filename) const;

    /**
     * @brief folder was deleted from the file system. Update the cached files
     * @param name folder path
     * @param notify when set to true, fire wxEVT_PROJ_FILE_REMOVED event (useful if you wish to update
     * other plugins such as git or subversion)
     */
    void FolderDeleted(const wxString& name, bool notify);

    void SetImportFileSpec(const wxString& importFileSpec) { this->m_importFileSpec = importFileSpec; }
    void SetName(const wxString& name) { this->m_name = name; }
    const wxString& GetName() const { return m_name; }

    /**
     * @brief file was renamed on the file system, update the cache and notify if needed
     */
    void FileRenamed(const wxString& oldname, const wxString& newname, bool notify);

    /**
     * @brief file was added on the file syste, update the cache and notify
     */
    void FileAdded(const wxString& filename, bool notify);

    /**
     * @brief file was added on the file system update the cache
     */
    void FolderAdded(const wxString& folderpath);

    /**
     * @brief files were deleted, remove them from the files cache and notify
     */
    void FilesDeleted(const wxArrayString& files, bool notify);

    /**
     * @brief synch the project folders with the file system
     */
    void SynchWithFileSystem();
};
#endif

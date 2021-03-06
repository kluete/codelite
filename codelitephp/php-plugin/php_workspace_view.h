#ifndef __php_workspace_view__
#define __php_workspace_view__

#include "php_ui.h"
#include "php_workspace.h"
#include <set>
#include <bitmap_loader.h>
#include "php_event.h"
#include <cl_command_event.h>
#include "wx_ordered_map.h"
#include "clTreeKeyboardInput.h"

class IManager;
class ItemData;

class PHPWorkspaceView : public PHPWorkspaceViewBase
{
    IManager* m_mgr;
    BitmapLoader::BitmapMap_t m_bitmaps;
    wxOrderedMap<wxTreeItemId, bool> m_itemsToSort;
    std::map<wxString, wxTreeItemId> m_filesItems;
    std::map<wxString, wxTreeItemId> m_foldersItems;
    clTreeKeyboardInput::Ptr_t m_keyboardHelper;

private:
    enum {
        ID_TOGGLE_AUTOMATIC_UPLOAD = wxID_HIGHEST + 1,
    };

protected:
    virtual void OnCollapse(wxCommandEvent& event);
    virtual void DoCollapseItem(wxTreeItemId& item);
    void OnFolderDropped(clCommandEvent& event);

    virtual void OnCollapseUI(wxUpdateUIEvent& event);
    virtual void OnSetupRemoteUploadUI(wxUpdateUIEvent& event);
    virtual void OnItemActivated(wxTreeEvent& event);
    virtual void OnMenu(wxTreeEvent& event);
    void OnWorkspaceLoaded(PHPEvent& event);
#if USE_SFTP
    virtual void OnSetupRemoteUpload(wxAuiToolBarEvent& event);
#endif
    virtual void OnWorkspaceOpenUI(wxUpdateUIEvent& event);
    virtual void OnActiveProjectSettings(wxCommandEvent& event);
    virtual void OnProjectSettings(wxCommandEvent& event);
    virtual void OnActiveProjectSettingsUI(wxUpdateUIEvent& event);
    void DoGetSelectedFiles(wxArrayString& files);
    // Helpers
    void DoSortItems();
    wxTreeItemId DoAddFolder(const wxString& project, const wxString& path);
    wxTreeItemId DoCreateFile(const wxTreeItemId& parent, const wxString& fullpath, const wxString& content = "");
    wxTreeItemId DoGetProject(const wxString& project);
    PHPProject::Ptr_t DoGetProjectForItem(const wxTreeItemId& item);
    wxTreeItemId DoGetSingleSelection();
    void DoGetSelectedItems(wxArrayTreeItemIds& items);

    wxString DoGetSelectedProject();
    ItemData* DoGetItemData(const wxTreeItemId& item);
    const ItemData* DoGetItemData(const wxTreeItemId& item) const;
    bool IsFolderItem(const wxTreeItemId& item);
    int DoGetItemImgIdx(const wxString& filename);
    wxBitmap DoGetBitmapForExt(const wxString& ext) const;
    void DoDeleteSelectedFileItem();
#if USE_SFTP
    void DoOpenSSHAccountManager();
#endif

    /**
     * @brief construct the project in the tree view
     * @param projectItem
     * @param project
     */
    void DoBuildProjectNode(const wxTreeItemId& projectItem, PHPProject::Ptr_t project);

    /**
     * @brief open an item into an editor
     */
    void DoOpenFile(const wxTreeItemId& item);

    void DoSetProjectActive(const wxString& projectName);

protected:
    // Handlers for PHPWorkspaceViewBase events.

    // Menu handlers
    DECLARE_EVENT_TABLE()

    void OnCloseWorkspace(wxCommandEvent& e);
    void OnReloadWorkspace(wxCommandEvent& e);
    void OnNewFolder(wxCommandEvent& e);
    void OnNewClass(wxCommandEvent& e);
    void OnDeleteProject(wxCommandEvent& e);
    void OnSetProjectActive(wxCommandEvent& e);
    void OnNewFile(wxCommandEvent& e);
    void OnDeleteFolder(wxCommandEvent& e);
    void OnOpenInExplorer(wxCommandEvent& e);
    void OnOpenShell(wxCommandEvent& e);
    void OnRetagWorkspace(wxCommandEvent& e);
    void OnAddExistingProject(wxCommandEvent& e);
    void OnFindInFiles(wxCommandEvent& e);
    void OnRemoveFile(wxCommandEvent& e);
    void OnOpenFile(wxCommandEvent& e);
    void OnRenameFile(wxCommandEvent& e);
    void OnRenameWorkspace(wxCommandEvent& e);
    void OnRunProject(wxCommandEvent& e);
    void OnMakeIndexPHP(wxCommandEvent& e);
    void OnSyncProjectWithFileSystem(wxCommandEvent& e);
    void OnOpenWithDefaultApp(wxCommandEvent& e);
    void OnRunActiveProject(clExecuteEvent& e);
    void OnStopExecutedProgram(clExecuteEvent& e);
    void OnIsProgramRunning(clExecuteEvent& e);
    void OnEditorChanged(wxCommandEvent& e);
    void OnFileRenamed(PHPEvent& e);
    void OnWorkspaceRenamed(PHPEvent& e);
    void OnToggleAutoUpload(wxCommandEvent& e);

    // Php parser events
    void OnPhpParserStarted(clParseEvent& event);
    void OnPhpParserProgress(clParseEvent& event);
    void OnPhpParserDone(clParseEvent& event);

public:
    /** Constructor */
    PHPWorkspaceView(wxWindow* parent, IManager* mgr);
    virtual ~PHPWorkspaceView();

    /**
     * @brief create a new project
     * @param name
     */
    void CreateNewProject(PHPProject::CreateData cd);

    void LoadWorkspace();
    void UnLoadWorkspace();

    void ReportParseThreadProgress(size_t curIndex, size_t total);
    void ReportParseThreadDone();
    void ReloadWorkspace(bool saveBeforeReload);
};

#endif // __php_workspace_view__

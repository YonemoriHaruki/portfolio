using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class TitleManager : MonoBehaviour
{
    public void LoadNextScene()
    {
        SceneManager.LoadScene("stage1");
        PlayerPrefs.DeleteAll();
    }

    public void BackTitleScene()
    {
        SceneManager.LoadScene("title");
        PlayerPrefs.DeleteAll();
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManagerScript : MonoBehaviour
{
    public enum GAME_STATUS { Play, Clear, Pause, GameOver };
    public static GAME_STATUS status;

    public static int tempUmiusiNum;

    [SerializeField]
    Text umiusiNumText, resultUmiusiText,levelNumText;

    [SerializeField]
    GameObject clearUI,gameOverUI;

    int stageUmiusiNum;         //データクラスを作ってそこから動かす★

    const string STAGE_NAME_PREFIX = "stage";
    const int MAX_STAGE_NUM = 5;


    int levelNum;   //現在の進行数
    int stageNum;   //読み込むステージ番号   


    // Start is called before the first frame update
    void Start()
    {
        // ステージ番号ロード
        stageNum = PlayerPrefs.GetInt("stageNum", 1);

        // 自分のシーンではない場合、ロードし直す
        if (!GetLoadSceneName().Equals(SceneManager.GetActiveScene().name))
        {
            LoadScene();
            return;
        }

        // レベル番号をロード
        levelNum = PlayerPrefs.GetInt("levelNum", 1);
        levelNumText.text = "Level " + levelNum;

        //ステージ内のうみうしの数を取得
        stageUmiusiNum = GameObject.FindGameObjectsWithTag("umiusi").Length;    //Findは重いので別の方法を考える★

        // これまでの獲得うみうし数をロード（初回は0）
        tempUmiusiNum = PlayerPrefs.GetInt("umiusiNum", 0);

        //ステータスをplayに
        status = GAME_STATUS.Play;
    }

    // Update is called once per frame
    void Update()
    {
        if (status == GAME_STATUS.Clear)
        {
            // 現在のステージで獲得したうみうしの数
            int getUmiusiNum = tempUmiusiNum - PlayerPrefs.GetInt("umiusiNum", 0);

            resultUmiusiText.text = getUmiusiNum.ToString().PadLeft(3) + "/" + stageUmiusiNum;
            clearUI.SetActive(true);

            //うみうしを保存
            PlayerPrefs.SetInt("umiusiNum", tempUmiusiNum);

            enabled = false;
        }
        else if(status == GAME_STATUS.GameOver)
        {
            Invoke("showGameOverUI", 3f);
            enabled = false;
            return;
        }
        umiusiNumText.text = tempUmiusiNum.ToString();
    }

    public void LoadCurrentScene()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    public void LoadNextScene()
    {
        PlayerPrefs.SetInt("levelNum", ++levelNum);

        stageNum = levelNum <= MAX_STAGE_NUM ? levelNum : Random.Range(1, MAX_STAGE_NUM + 1);
        PlayerPrefs.SetInt("stageNum", stageNum);

        LoadScene();
    }

    private void showGameOverUI()
    {
        gameOverUI.SetActive(true);
    }

    private string GetLoadSceneName()
    {
        return STAGE_NAME_PREFIX + stageNum;
    }

    public void LoadScene()
    {
        SceneManager.LoadScene(GetLoadSceneName());
    }
}

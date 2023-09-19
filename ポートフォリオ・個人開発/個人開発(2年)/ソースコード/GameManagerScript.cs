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

    int stageUmiusiNum;         //�f�[�^�N���X������Ă������瓮������

    const string STAGE_NAME_PREFIX = "stage";
    const int MAX_STAGE_NUM = 5;


    int levelNum;   //���݂̐i�s��
    int stageNum;   //�ǂݍ��ރX�e�[�W�ԍ�   


    // Start is called before the first frame update
    void Start()
    {
        // �X�e�[�W�ԍ����[�h
        stageNum = PlayerPrefs.GetInt("stageNum", 1);

        // �����̃V�[���ł͂Ȃ��ꍇ�A���[�h������
        if (!GetLoadSceneName().Equals(SceneManager.GetActiveScene().name))
        {
            LoadScene();
            return;
        }

        // ���x���ԍ������[�h
        levelNum = PlayerPrefs.GetInt("levelNum", 1);
        levelNumText.text = "Level " + levelNum;

        //�X�e�[�W���̂��݂����̐����擾
        stageUmiusiNum = GameObject.FindGameObjectsWithTag("umiusi").Length;    //Find�͏d���̂ŕʂ̕��@���l���遚

        // ����܂ł̊l�����݂����������[�h�i�����0�j
        tempUmiusiNum = PlayerPrefs.GetInt("umiusiNum", 0);

        //�X�e�[�^�X��play��
        status = GAME_STATUS.Play;
    }

    // Update is called once per frame
    void Update()
    {
        if (status == GAME_STATUS.Clear)
        {
            // ���݂̃X�e�[�W�Ŋl���������݂����̐�
            int getUmiusiNum = tempUmiusiNum - PlayerPrefs.GetInt("umiusiNum", 0);

            resultUmiusiText.text = getUmiusiNum.ToString().PadLeft(3) + "/" + stageUmiusiNum;
            clearUI.SetActive(true);

            //���݂�����ۑ�
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

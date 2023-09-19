using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CharacterChange : MonoBehaviour
{
    [SerializeField] private GameObject[] Character;


    private int _selected = 0;
    void Start()
    {
        _selected = PlayerPrefs.GetInt("CharacterSelect", 0);
        Character[_selected].SetActive(true);

      
    }
    public void Right()                                     //右ボタンにセット
    {
        Character[_selected].SetActive(false);
        _selected++;
        if (_selected >= Character.Length)
            _selected = 0;
        Character[_selected].SetActive(true);
    }
    public void Left()                                      //左ボタンにセット
    {
        Character[_selected].SetActive(false);
        _selected--;
        if (_selected < 0)
            _selected = Character.Length - 1;
        Character[_selected].SetActive(true);
    }
    public void SelectBall()                        //決定ボタンにセット
    {
       // test umiusi;
       // GameObject test = GameObject.Find("Have");
       // umiusi = test.GetComponent<test>();
       // if (umiusi.HaveUmiusi >= 100)
        //{
          // Debug.Log("うみうしを100消費しました！");
          //  umiusi.HaveUmiusi -= 100;
            PlayerPrefs.SetInt("CharacterSelect", _selected);                  //選んだキャラクターをプレハブにセット
            SceneManager.LoadScene("stage1");                                       //選択ボタンを押したらタイトルに戻る
       // }
        //else
        //{
       //     Debug.Log("うみうしが足りません");
       // }
     
    }
}

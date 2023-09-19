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
    public void Right()                                     //�E�{�^���ɃZ�b�g
    {
        Character[_selected].SetActive(false);
        _selected++;
        if (_selected >= Character.Length)
            _selected = 0;
        Character[_selected].SetActive(true);
    }
    public void Left()                                      //���{�^���ɃZ�b�g
    {
        Character[_selected].SetActive(false);
        _selected--;
        if (_selected < 0)
            _selected = Character.Length - 1;
        Character[_selected].SetActive(true);
    }
    public void SelectBall()                        //����{�^���ɃZ�b�g
    {
       // test umiusi;
       // GameObject test = GameObject.Find("Have");
       // umiusi = test.GetComponent<test>();
       // if (umiusi.HaveUmiusi >= 100)
        //{
          // Debug.Log("���݂�����100����܂����I");
          //  umiusi.HaveUmiusi -= 100;
            PlayerPrefs.SetInt("CharacterSelect", _selected);                  //�I�񂾃L�����N�^�[���v���n�u�ɃZ�b�g
            SceneManager.LoadScene("stage1");                                       //�I���{�^������������^�C�g���ɖ߂�
       // }
        //else
        //{
       //     Debug.Log("���݂���������܂���");
       // }
     
    }
}

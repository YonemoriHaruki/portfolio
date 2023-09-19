using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CharaInput : MonoBehaviour
{
    [SerializeField] GameObject[] CharacterPrefabs;
    [SerializeField] GameObject MovementBase;
    // Start is called before the first frame update
    void Start()
    { 
        int select = PlayerPrefs.GetInt("CharacterSelect", 0);
        GameObject CharacterObj = CharacterPrefabs[select];

        CharacterPrefabs[select] = (GameObject)Instantiate(CharacterPrefabs[select], this.transform.position, Quaternion.identity);
        CharacterPrefabs[select].transform.parent = MovementBase.transform;
    }
}

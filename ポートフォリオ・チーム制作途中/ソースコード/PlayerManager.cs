using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    [SerializeField] private GameObject Player1;
    [SerializeField] private GameObject Player2;
    [SerializeField] private GameObject Player3;
    [SerializeField] private GameObject Player4;
    
    float[] playerX = new float[4];
    float[] playerZ = new float[4];

    int posCom0;
    int posCom1;
    int posCom2;
    int posCom3;
    public int max;

    public bool Gun12Active;
    public bool Gun23Active;
    public bool Gun34Active;
    public bool Gun41Active;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        playerX[0] = Player1.transform.position.x;
        playerX[1] = Player2.transform.position.x;
        playerX[2] = Player3.transform.position.x;
        playerX[3] = Player4.transform.position.x;

        playerZ[0] = Player1.transform.position.z;
        playerZ[1] = Player2.transform.position.z;
        playerZ[2] = Player3.transform.position.z;
        playerZ[3] = Player4.transform.position.z;

       
    }

    public void PlayerPosCom()
    {
        max = 0;
        posCom0 = 0;
        posCom1 = 0;
        posCom2 = 0;
        posCom3 = 0;

        Gun12Active = false;
        Gun23Active = false;
        Gun34Active = false;
        Gun41Active = false;

        for (int i = 0; i < 4; i++)                                                                //プレイヤーの位置判定
        {
            if (playerX[i] <= 0 && playerZ[i] <= 0)          //X- : Z-
            {
                posCom0 += 1;
            }
            else if (playerX[i] <= 0 && playerZ[i] >= 0)          //X- : Z+
            {
                posCom1 += 1;
            }
            else if (playerX[i] >= 0 && playerZ[i] >= 0)          //X+ : Z+
            {
                posCom2 += 1;
            }
            else if (playerX[i] >= 0 && playerZ[i] <= 0)          //X+ : Z-
            {
                posCom3 += 1;
            }
        }

        max = posCom0;                                      // 一番多い人数を判定

        if (max < posCom1)
        {
            max = posCom1;
        }
        else if (max < posCom2)
        {
            max = posCom2;
        }
        else if (max < posCom3)
        {
            max = posCom3;
        }

        if (max == posCom0)                                 //一番多い人数と一緒の場所を洗い出す
        {
            Gun41Active = true;
        }
        if (max == posCom1)
        {
            Gun12Active = true;
        }
        if (max == posCom2)
        {
            Gun23Active = true;
        }
        if (max == posCom3)
        {
            Gun34Active = true;
        }

    }
}

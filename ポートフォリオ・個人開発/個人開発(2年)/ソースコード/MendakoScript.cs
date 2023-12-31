using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MendakoScript : MonoBehaviour
{
    float speed = 100f;

    public bool isGet;             // 獲得済みフラグ
    bool isSpeedUp = false;
    float lifeTime = 3.0f;  // 獲得後の生存時間 
    [SerializeField] float speedUpTime = 3.0f;

    GameObject Player;
    PlayerScript playerCode;

    


    void Start()
    {
 
    }

    void Update()
    {
        if(Player == null)
        {
            Player = GameObject.FindGameObjectWithTag("Player");
            playerCode = Player.GetComponent<PlayerScript>();
        }

        // 獲得後
        if (isGet)
        {
            // 素早く回転
            transform.Rotate(Vector3.up * speed * 10f * Time.deltaTime, Space.World);

            // 生存時間を減らす
            lifeTime -= Time.deltaTime;

            // 生存時間が0以下になったら消滅
            if (lifeTime <= 0)
            {
                gameObject.SetActive(false);
            }
        }

        // 獲得前
        else
        {
            // ゆっくり回転
            transform.Rotate(Vector3.up * speed * Time.deltaTime, Space.World);
        }

        if(isSpeedUp)
        {
            speedUpTime -= Time.deltaTime;
            if (speedUpTime <= 0.0f)
            {
                ResetSpeed();
                isGet = false;
                isSpeedUp = false;
            }
        }
    }

    public void OnTriggerEnter(Collider other)
    {
        // プレイヤーが接触で獲得判定
        if (!isGet && !isSpeedUp && other.CompareTag("Player"))
        {
            isGet = true;

            GetComponent<AudioSource>().Play();

            GetSpeed();

            isSpeedUp = true;
        }
    }

    public void GetSpeed()
    {
        playerCode.speed = 15f;
    }

    public void ResetSpeed()
    {
        
        playerCode.speed = 6f;
    }

  
}

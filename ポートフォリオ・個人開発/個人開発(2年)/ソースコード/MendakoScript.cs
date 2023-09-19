using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MendakoScript : MonoBehaviour
{
    float speed = 100f;

    public bool isGet;             // Šl“¾Ï‚İƒtƒ‰ƒO
    bool isSpeedUp = false;
    float lifeTime = 3.0f;  // Šl“¾Œã‚Ì¶‘¶ŠÔ 
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

        // Šl“¾Œã
        if (isGet)
        {
            // ‘f‘‚­‰ñ“]
            transform.Rotate(Vector3.up * speed * 10f * Time.deltaTime, Space.World);

            // ¶‘¶ŠÔ‚ğŒ¸‚ç‚·
            lifeTime -= Time.deltaTime;

            // ¶‘¶ŠÔ‚ª0ˆÈ‰º‚É‚È‚Á‚½‚çÁ–Å
            if (lifeTime <= 0)
            {
                gameObject.SetActive(false);
            }
        }

        // Šl“¾‘O
        else
        {
            // ‚ä‚Á‚­‚è‰ñ“]
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
        // ƒvƒŒƒCƒ„[‚ªÚG‚ÅŠl“¾”»’è
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

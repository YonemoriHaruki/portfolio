using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MendakoScript : MonoBehaviour
{
    float speed = 100f;

    public bool isGet;             // �l���ς݃t���O
    bool isSpeedUp = false;
    float lifeTime = 3.0f;  // �l����̐������� 
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

        // �l����
        if (isGet)
        {
            // �f������]
            transform.Rotate(Vector3.up * speed * 10f * Time.deltaTime, Space.World);

            // �������Ԃ����炷
            lifeTime -= Time.deltaTime;

            // �������Ԃ�0�ȉ��ɂȂ��������
            if (lifeTime <= 0)
            {
                gameObject.SetActive(false);
            }
        }

        // �l���O
        else
        {
            // ��������]
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
        // �v���C���[���ڐG�Ŋl������
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

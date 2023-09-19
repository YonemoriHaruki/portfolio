using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotate : MonoBehaviour
{


    [SerializeField] float rotateSpeed = 0.1f;
    [SerializeField] float rotateTime;
    private float time;

    public bool rotateActive;
    void Start()
    {
        time = 0.0f;
        rotateActive = false;
    }

    void Update()
    {
        //�o�ߎ��Ԃ��J�E���g
        time += Time.deltaTime;

        if(time >= rotateTime)
        { 
            rotateActive = true;
            transform.Rotate(new Vector3(0, rotateSpeed, 0));
            if (Input.GetKeyDown("space"))                          //★★★テスト用
            {
                rotateSpeed = -rotateSpeed;
            }
        }
    }
}

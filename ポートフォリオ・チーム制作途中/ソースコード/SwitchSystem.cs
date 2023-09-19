using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SocialPlatforms.Impl;

public class SwitchSystem : MonoBehaviour
{
    float bottomY = 0.6f;
    float speed = 0.5f;

    bool active;
    [SerializeField] private WaterShot WaterShotScript;
    [SerializeField] private ParticleSystem particle;

    [SerializeField] Rotate RotateScript;

    float repeatSpan = 8;
    float waterStopElapsedTime = 0;
    float bottomPosY;
    bool switchReset;
   

    void Start()
    {
        repeatSpan = 7;
        waterStopElapsedTime = 0;
        bottomPosY = transform.position.y;
        switchReset = false;
    }

    // Update is called once per frame
    void Update()
    { 
        if (active && transform.position.y > bottomY)
        {
            transform.position -= Vector3.up * speed * Time.deltaTime;
           
        }
        if (active)
        {
            WaterShotScript.waterActive = false;
            switchReset = false;
            waterStopElapsedTime += Time.deltaTime;
        }
        if(waterStopElapsedTime >= repeatSpan)          //押された状態から元に戻す
        {
            active = false;
            WaterShotScript.waterActive = true;
            waterStopElapsedTime = 0;
            switchReset = true;
        }
        if (active == false && transform.position.y < bottomPosY&&switchReset == true)  
        {
            transform.position += Vector3.up * speed * Time.deltaTime;
        }

        if(active == false && RotateScript.rotateActive)                    //回転が始まったらスイッチ本体を消す
        {
            transform.position -= Vector3.up * speed * Time.deltaTime;
            Destroy(this.gameObject, 2.0f);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if(!active && other.CompareTag("player"))
        {
            active = true;
        }
    }
}

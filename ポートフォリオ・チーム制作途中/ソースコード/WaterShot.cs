using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class WaterShot : MonoBehaviour
{
    private float repeatSpan;    //再生繰り返す間隔
    private float playElapsedTime;   //再生経過時間
    private float stopElapsedTime;   //停止経過時間
    int rand;
    private float shotSpan;         //ショット間隔
    private float shotElapsedTime;  //ショット経過時間
    [SerializeField] private ParticleSystem particle;
    [SerializeField] private PlayerManager playerManager;


    public bool waterActive;

   
    

    // Start is called before the first frame update
    void Start()
    {
        repeatSpan = 3;    //再生間隔を設定
        playElapsedTime = 0;   //再生経過時間をリセット
        stopElapsedTime = 0;    //停止経過時間をリセット

        shotSpan = 5;   //ショット間隔を設定
        shotElapsedTime = 0; //ショット経過時間をリセット
        waterActive = true;
    }

    // Update is called once per frame
    void Update()
    {
        
        shotElapsedTime += Time.deltaTime;  //ショット経過時間をカウント
        if (shotElapsedTime >= shotSpan)
        {
            playerManager.PlayerPosCom();       //プレイヤーの場所を比較させて水を打つか判定
                if(waterActive)
                {
                    Play();
                }
            shotElapsedTime = 0;        //ショット経過時間をリセット
        }
       
    }

    // 1. 再生
    public void Play()
    {
        playElapsedTime += Time.deltaTime;     //再生経過時間をカウント
        stopElapsedTime += Time.deltaTime;     //停止経過時間をカウント
        if (playElapsedTime <= repeatSpan && stopElapsedTime <= repeatSpan)
        {
            particle.Play();
            playElapsedTime = 0;   //再生経過時間をリセットする
        }
    }

    // 2. 一時停止
    public void Pause()
    {
        particle.Pause();
    }

    // 3. 停止
    public void Stop()
    {
        particle.Stop();
    }
}

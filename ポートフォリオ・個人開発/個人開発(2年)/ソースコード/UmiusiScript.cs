using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using UnityEngine;
 
public class UmiusiScript : MonoBehaviour
{
    float speed = 100f;
 
    bool isGet;             // 獲得済みフラグ
    float lifeTime = 0.5f;  // 獲得後の生存時間 

    [SerializeField]
    private ParticleSystem StarParticle;

    void Start()
    {
 
    }
 
    void Update()
    {
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
                Destroy(gameObject);
            }
        }
        // 獲得前
        else
        {
            // ゆっくり回転
            transform.Rotate(Vector3.up * speed * Time.deltaTime, Space.World);
        }
    }
 
    void OnTriggerEnter(Collider other)
    {
        // プレイヤーが接触で獲得判定
        if (!isGet && other.CompareTag("Player"))
        {
            isGet = true;

            GetComponent<AudioSource>().Play();

            GameManagerScript.tempUmiusiNum++;
            Debug.Log("うみうしの数:"+GameManagerScript.tempUmiusiNum);

            ParticleSystem newParticle = Instantiate(StarParticle);
            newParticle.transform.position = this.transform.position;
            newParticle.Play();

            Destroy(newParticle.gameObject, 1.5f);
            
        }
    }
}
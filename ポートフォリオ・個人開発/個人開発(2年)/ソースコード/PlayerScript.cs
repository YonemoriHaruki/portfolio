using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI; 

public class PlayerScript : MonoBehaviour
{
    Animator animator;

    public bool isRunning;
 
    public float sensitivity = 1f;                  //感度設定
    const float LOAD_WIDTH = 6f;                    //道幅
    const float MOVE_MAX = 2.5f;                    //道の中心から移動できる最大距離
    Vector3 previousPos, currentPos;                //1フレーム前のマウス位置  ,  現在のマウス位置

    Vector3 dest;                                   //次の目的地、クリア時に使用
    public float speed = 6f;

    private GameObject Mendako;

    void Start()
    {
        animator = GetComponent<Animator>();
        Mendako = GameObject.Find("Mendako");
    }
 
    void Update()
    {
          // クリア時の処理
        if (GameManagerScript.status == GameManagerScript.GAME_STATUS.Clear)
        {
            // 目的地の方向を向く
            transform.LookAt(dest);
 
            // 目的地の方向に移動させる
            Vector3 dir = (dest - transform.position).normalized;
            transform.position += dir * speed * Time.deltaTime;
 
            // 目的地に十分近づいたら、最終演出
            if ((dest - transform.position).magnitude < 0.5f)
            {
                transform.position = dest;
                transform.rotation = Quaternion.Euler(0, 180, 0);
                animator.SetBool("IsRunning", false);
                animator.SetTrigger("Clear");

 
                enabled = false;
            }
            return;
        }

        // プレイ以外なら無効にする
        if (GameManagerScript.status != GameManagerScript.GAME_STATUS.Play)
        {
            animator.SetBool("IsRunning", false);
            return;
        }

        if (Input.GetMouseButtonDown(0))                     //入力されたか？
        {
            previousPos = Input.mousePosition;
        }

        if(Input.GetMouseButton(0))                         //押され続けてるか？
        {
            //スワイプによる移動距離を取得
            currentPos = Input.mousePosition;                                                       //最新のマウス位置　
            float diffDistance = (currentPos.x - previousPos.x) / Screen.width * LOAD_WIDTH;        //スクリーン座標からワールド座標への変換(解像度基準から道幅基準に置き変え)
            diffDistance *= sensitivity;                                                            //移動距離に感度をかけて感度を調整する

            //次のローカルｘ座標を設定　＊道の外に出ないように
            float newX = Mathf.Clamp(transform.localPosition.x + diffDistance, -MOVE_MAX,MOVE_MAX);
            transform.localPosition = new Vector3(newX,0,0);

            //タップ位置を更新
            previousPos = currentPos;

           
        }

        animator.SetBool("IsRunning", isRunning);


        if (Mendako != null)
        {
            if (Mendako.GetComponent<MendakoScript>().isGet)
            {
                GetParticle();
            }
            else if (!Mendako.GetComponent<MendakoScript>().isGet)
            {
                ResetParticle();
            }
        }
    }
    
    public void Clear(Vector3 pos)
    {
        GameManagerScript.status = GameManagerScript.GAME_STATUS.Clear;
        dest = pos;
    }

    public void TakeDamage()
    {
        animator.SetTrigger("Damaged");
        GameManagerScript.status = GameManagerScript.GAME_STATUS.GameOver;
    }
    public void GetParticle()
    {
        GameObject Player = GameObject.Find("Player");
        GameObject mendakoParticle = transform.Find("mendakoParticle").gameObject;
        GameObject powerParticle = transform.Find("power").gameObject;
        mendakoParticle.SetActive(true);
        powerParticle.SetActive(true);
    }

    public void ResetParticle()
    {
        GameObject Player = GameObject.Find("Player");
        GameObject mendakoParticle = transform.Find("mendakoParticle").gameObject;
        GameObject powerParticle = transform.Find("power").gameObject;
        mendakoParticle.SetActive(false);
        powerParticle.SetActive(false);
    }
}



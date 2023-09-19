using PathCreation;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementBaseScript : MonoBehaviour
{
    [SerializeField]
    PathCreator pathCreator;

    private GameObject player;
    private PlayerScript playerScript;

      [SerializeField]
    GameObject helpUI;

    [SerializeField]
    GameObject dashUI;

    float speed = 6f;
    Vector3 endPos;

    float moveDistance;

    // Start is called before the first frame update
    void Start()
    {
        

        endPos = pathCreator.path.GetPoint(pathCreator.path.NumPoints - 1);      //経路の最終地点の座標をendPosに代入　　*アセットが提供する GetPointメソッドを使用これは引数に経路上の地点のインデックスを指定することで、その位置を取得できるメソッドです。
    }

    // Update is called once per frame
    void Update()
    {
        if(player == null)
        {
            player = GameObject.FindGameObjectWithTag("Player");
            playerScript = player.GetComponent<PlayerScript>();
        }
        //プレイ中以外は無効にする
        if(GameManagerScript.status != GameManagerScript.GAME_STATUS.Play)
        {
            helpUI.SetActive(false);
            dashUI.SetActive(false);
            return;
        }

        //タップ中は走る
       if (Input.GetMouseButton(0))
        {
         moveDistance += playerScript.speed * Time.deltaTime;
         moveDistance += speed * Time.deltaTime;
         transform.position = pathCreator.path.GetPointAtDistance(moveDistance, EndOfPathInstruction.Stop);      //セットが提供する、GetPointAtDistanceメソッドを使用 開始地点からの経路上の距離を指定することで、その点の座標を取得しています。
                                                                                                                //第１引数：開始地点からの経路上の距離
                                                                                                                //第２引数：最終地点を超える距離を指定した場合の動作（今回は超えたら最終地点を指す設定
         transform.rotation = pathCreator.path.GetRotationAtDistance(moveDistance, EndOfPathInstruction.Stop);     //回転を取得するメソッドとなります。

            playerScript.isRunning = true;
          helpUI.SetActive(false);
            dashUI.SetActive(false);
        }
        else if (Input.GetMouseButtonUp(0))
        {
            playerScript.isRunning = false;
            helpUI.SetActive(true);
            dashUI.SetActive(true); 
        }
        
    }
}

using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System;
using UnityEngine.Audio; 

public class GameManager : MonoBehaviour {

	public GameObject playerPrefab; 
	public Text continueText;
	public Text scoreText; 
	public Text titleText;
	public AudioSource runningMusic; 
	public AudioSource screamSound; 

	private float timeElapsed = 0f;
	private float bestTime = 0f;
	private float blinkTime = 0f; 
	private bool blink; 
	private bool gameStarted; 
	private TimeManager timeManager; 
	private GameObject player; 
	private GameObject floor; 
	private Spawner spawner;
	private bool beatBestTime;

	void Awake(){
		floor = GameObject.Find ("Ground");
		spawner = GameObject.Find ("Spawner").GetComponent<Spawner> ();
		timeManager = GetComponent <TimeManager> (); 
	}

	// Use this for initialization
	void Start () {
		var floorHeight = floor.transform.localScale.y;
		var pos = floor.transform.position; 
		pos.x = 0;
		pos.y = -((Screen.height / PixelPerfectCamera.pixelsToUnits) / 2) + (floorHeight / 2); 
		floor.transform.position = pos; 

		screamSound.Pause();
		runningMusic.Pause();
		spawner.active = false; 
		Time.timeScale = 0; 

		continueText.text = "Press any button to run for your life!";
		titleText.text = "Survival of the Baby Iguana";
		bestTime = PlayerPrefs.GetFloat ("BestTime"); 
	}
	
	// Update is called once per frame
	void Update () {

		if (!gameStarted && Time.timeScale == 0) { 

			if (Input.anyKeyDown) { 

				timeManager.ManipulateTime (1, 1f); 
				ResetGame (); 

			}
		}

		if (!gameStarted) { 
			blinkTime++; 

			if (blinkTime % 20 == 0) { 
				blink = !blink; 
			} 

			continueText.canvasRenderer.SetAlpha (blink ? 0 : 3); 

			titleText.canvasRenderer.SetAlpha (1);

			var textColor = beatBestTime ? "DF82E1FF" : "#F17800FF"; 

			scoreText.text = "Time: " + FormatTime (timeElapsed) + "\n<color="+textColor+">Best: " + FormatTime (bestTime)+"</color>"; 
		}else{ 
			timeElapsed += Time.deltaTime;
			scoreText.text = "Time: "+FormatTime(timeElapsed);
		}
	}

	void OnPlayerKilled(){ 

		screamSound.Play();
		spawner.active = false; 
		runningMusic.Pause();
		var playerDestroyScript = player.GetComponent<DestroyOffscreen> (); 
		playerDestroyScript.DestroyCallback -= OnPlayerKilled;

		player.GetComponent<Rigidbody2D> ().velocity = Vector2.zero; 
		timeManager.ManipulateTime (0, 5.5f); 
		gameStarted = false; 

		titleText.text = "";
		continueText.text = "You're not completely dead yet, run again!";

		if (timeElapsed > bestTime) { 
			bestTime = timeElapsed; 
			PlayerPrefs.SetFloat("BestTime", bestTime); 
			beatBestTime = true; 
		}

	}

	void ResetGame() { 
		screamSound.Pause();
		spawner.active = true; 
		runningMusic.Play();
		player = GameObjectUtil.Instantiate (playerPrefab, new Vector3 (0, (Screen.height / PixelPerfectCamera.pixelsToUnits) / 1.7f + 100, 0)); 

		var playerDestroyScript = player.GetComponent<DestroyOffscreen> (); 
		playerDestroyScript.DestroyCallback += OnPlayerKilled;

		gameStarted = true; 

		continueText.canvasRenderer.SetAlpha (0);
		titleText.canvasRenderer.SetAlpha (0);

		timeElapsed = 0; 
		beatBestTime = false;
	
	}

	string FormatTime(float value){ 
		TimeSpan t = TimeSpan.FromSeconds (value); 

		return string.Format("{0:D2}:{1:D2}",t.Minutes, t.Seconds); 
	}
}

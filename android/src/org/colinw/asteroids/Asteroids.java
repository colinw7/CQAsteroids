package org.colinw.asteroids;

import android.app.Activity;
import android.os.Bundle;

public class Asteroids extends Activity {
  private AsteroidsView view;
  
  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    
    view = new AsteroidsView(this);
    
    setContentView(view);
    
    view.requestFocus();
  }
}

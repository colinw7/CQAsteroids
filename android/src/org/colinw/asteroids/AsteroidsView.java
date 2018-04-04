package org.colinw.asteroids;

import java.util.Timer;
import java.util.TimerTask;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Paint;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Canvas;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;

public class AsteroidsView extends View {
  private class ViewTimerTask extends TimerTask {
    private AsteroidsView view_;
    
    public ViewTimerTask(AsteroidsView view) {
      view_ = view;
    }
    
    @Override
    public void run() {
      view_.update();
      
      view_.postInvalidate();
    }
  }
  
  private Asteroids          asteroids_;
  
  private AsteroidsObjectMgr object_mgr_;
  private AsteroidsSaucerMgr saucer_mgr_;
  private AsteroidsRockMgr   rock_mgr_;

  private AsteroidsShip      ship_;
  private AsteroidsScore     score_;

  private LFont              lfont_;
  
  private int                level_;
  private boolean            game_over_;
  
  private Timer              timer_;
  
  private Canvas             canvas_;
  private Paint              fg_paint_;
  private double             w_, h_;
  private BBox               left_bbox_;
  private BBox               right_bbox_;
  private BBox               fire_bbox_;
  private BBox               thrust_bbox_;

  public AsteroidsView(Context context) {
    super(context);
  
    asteroids_ = (Asteroids) context;
    
    setFocusable(true);
    setFocusableInTouchMode(true);

    //------

    game_over_ = false;

    rock_mgr_   = new AsteroidsRockMgr  (this);
    object_mgr_ = new AsteroidsObjectMgr(this);
    saucer_mgr_ = new AsteroidsSaucerMgr(this);

    score_ = new AsteroidsScore(this);
    
    lfont_ = new LFont();

    ship_  = object_mgr_.createShip();

    level_ = 0;

    nextLevel();
    
    timer_ = new Timer();
    
    timer_.schedule(new ViewTimerTask(this), 10, 60);
  }
  
  AsteroidsObjectMgr getObjectMgr() { return object_mgr_; }
  AsteroidsSaucerMgr getSaucerMgr() { return saucer_mgr_; }
  AsteroidsRockMgr   getRockMgr  () { return rock_mgr_  ; }

  AsteroidsShip getShip() { return ship_; }

  void newGame() {
    game_over_ = false;

    score_     .reset();
    rock_mgr_  .removeAll();
    object_mgr_.removeAll();

    ship_  = object_mgr_.createShip();
    
    level_ = 0;
    
    nextLevel();
  }

  void nextLevel() {
    ++level_;

    object_mgr_.createBigRock(0.0, 0.0, 0.0,  0.003,  0.003, 0.003);
    object_mgr_.createBigRock(1.0, 0.0, 0.0, -0.004,  0.004, 0.004);
    object_mgr_.createBigRock(0.0, 1.0, 0.0,  0.005, -0.005, 0.005);
    object_mgr_.createBigRock(1.0, 1.0, 0.0, -0.006, -0.006, 0.006);
  }

  void shipTurnLeft() {
    ship_.turnLeft();
  }

  void shipTurnRight() {
    ship_.turnRight();
  }

  void shipThrust() {
    ship_.thrust();
  }

  boolean shipFire() {
    return ship_.fire();
  }

  void shipHyperspace() {
    ship_.hyperspace();
  }

  void update() {
    object_mgr_.move();

    if (! game_over_)
      object_mgr_.intersect();
    
    object_mgr_.cleanup();
  }

  void drawLine(double x1, double y1, double x2, double y2) {
    canvas_.drawLine((float) (w_*x1), (float) (h_*(1.0 - y1)), (float) (w_*x2), (float) (h_*(1.0 - y2)), fg_paint_);
  }

  void drawChar(double x, double y, double size, char c) {
    LineChar lc = lfont_.getFontDef(c);

    for (int i = 0; i < lc.num_lines; i++) {
      Line line = lc.lines[i];

      double x1 = line.start.x()*size;
      double y1 = (1.0 - line.start.y())*size;
      double x2 = line.end  .x()*size;
      double y2 = (1.0 - line.end  .y())*size;

      canvas_.drawLine((float) (w_*(x + x1)), (float) (h_*(y + y1)), (float) (w_*(x + x2)), (float) (h_*(y + y2)), fg_paint_);
    }
  }

  void addScore(int score) {
    score_.add(score);
  }

  void shipDestroyed() {
    if (score_.numLives() > 0)
      score_.die();
    else {
      ship_.setVisible(false);

      game_over_ = true;
    }
  }

  @Override
  protected void onSizeChanged(int w, int h, int oldw, int oldh) {
    super.onSizeChanged(w, h, oldw, oldh);
  }
  
  @Override
  protected void onDraw(Canvas canvas) {
    canvas_ = canvas;
    
    w_ = canvas_.getWidth();
    h_ = canvas_.getHeight();
    
    Paint bg_paint = new Paint();
    bg_paint.setColor(0xFF000000);
    
    canvas.drawRect(0, 0, canvas.getWidth(), canvas.getHeight(), bg_paint);

    fg_paint_ = new Paint();
    fg_paint_.setColor(0xFFFFFFFF);

    object_mgr_.draw();

    score_.draw();

    if (! game_over_) {
      if (rock_mgr_.getNumRocks() == 0)
        nextLevel();
    }
    
    Resources res = asteroids_.getResources();
    
    Bitmap leftBitmap   = BitmapFactory.decodeResource(res, R.drawable.asteroids_left);
    Bitmap rightBitmap  = BitmapFactory.decodeResource(res, R.drawable.asteroids_right);
    Bitmap thrustBitmap = BitmapFactory.decodeResource(res, R.drawable.asteroids_thrust);
    Bitmap fireBitmap   = BitmapFactory.decodeResource(res, R.drawable.asteroids_shoot);

    left_bbox_   = new BBox(      8, h_ -  80,     130, h_ - 16); // 122x64
    right_bbox_  = new BBox(      8, h_ - 160,     130, h_ - 96); // 122x64
    thrust_bbox_ = new BBox(w_ - 80, h_ -  80, w_ - 16, h_     ); // 64x80
    fire_bbox_   = new BBox(w_ - 80, h_ - 160, w_ - 16, h_ - 96); // 64x64
    
    canvas.drawBitmap(leftBitmap  , (float) left_bbox_  .xmin(), (float) left_bbox_  .ymin(), bg_paint);
    canvas.drawBitmap(rightBitmap , (float) right_bbox_ .xmin(), (float) right_bbox_ .ymin(), bg_paint);
    canvas.drawBitmap(thrustBitmap, (float) thrust_bbox_.xmin(), (float) thrust_bbox_.ymin(), bg_paint);
    canvas.drawBitmap(fireBitmap  , (float) fire_bbox_  .xmin(), (float) fire_bbox_  .ymin(), bg_paint);

    if (game_over_) {
      double x = 0.07;
      double y = 0.46;
      double s = 0.07;

      drawChar(x += 0.08, y, s, 'G');
      drawChar(x += 0.08, y, s, 'A');
      drawChar(x += 0.08, y, s, 'M');
      drawChar(x += 0.08, y, s, 'E');
      drawChar(x += 0.08, y, s, ' ');
      drawChar(x += 0.08, y, s, 'O');
      drawChar(x += 0.08, y, s, 'V');
      drawChar(x += 0.08, y, s, 'E');
      drawChar(x += 0.08, y, s, 'R');
    }
  }
  
  @Override
  public boolean onTouchEvent(MotionEvent event) {
    if (event.getAction() != MotionEvent.ACTION_DOWN)
      return super.onTouchEvent(event);
  
    if (game_over_) { newGame(); return true; }
    
    if     (left_bbox_   .inside(event.getX(), event.getY()))
      shipTurnRight();
    else if (right_bbox_ .inside(event.getX(), event.getY()))
      shipTurnLeft();
    else if (thrust_bbox_.inside(event.getX(), event.getY()))
      shipThrust();
    else if (fire_bbox_  .inside(event.getX(), event.getY()))
      shipFire();
    
    return true;
  }
  
  @Override
  public boolean onKeyDown(int keyCode, KeyEvent event) {
    if (game_over_) { newGame(); return true; }
    
    switch (keyCode) {
    case KeyEvent.KEYCODE_DPAD_LEFT:
    case KeyEvent.KEYCODE_DPAD_UP:
      shipTurnLeft();
      break;
    case KeyEvent.KEYCODE_DPAD_RIGHT:
    case KeyEvent.KEYCODE_DPAD_DOWN:
      shipTurnRight();
      break;
    case KeyEvent.KEYCODE_SPACE:
      shipFire();
      break;
    case KeyEvent.KEYCODE_CTRL_LEFT:
      shipThrust();
      break;
    default:
      return super.onKeyDown(keyCode, event);
    }
    return true;
  }
}
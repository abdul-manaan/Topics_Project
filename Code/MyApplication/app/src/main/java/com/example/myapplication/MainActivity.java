package com.example.myapplication;

import android.Manifest;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import java.util.List;

import static com.example.myapplication.R.id.monitorApp;
import static com.example.myapplication.R.id.sessionTime;
import static java.lang.Integer.parseInt;
import static java.lang.System.out;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if(ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        }




    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(int mem,int oom,String fname,int session ,String appName);

    public void callMe(View view) {

        out.println("LOA");

        EditText _fname = findViewById(R.id.fileName);
        EditText _oom = findViewById(R.id.oomAdj);
        EditText _mem = findViewById(R.id.memoryLimit);
        EditText _sess = findViewById(sessionTime);
        EditText _app = findViewById(monitorApp);
        String fame = _fname.getText().toString();
        String oom = _oom.getText().toString();
        String mem = _mem.getText().toString();
        String sess = _sess.getText().toString();
        String app = _app.getText().toString();
        out.printf("%s %d %s",fame, parseInt(oom), parseInt(mem));
        out.println(stringFromJNI( parseInt(oom), parseInt(mem), fame, parseInt(sess), app));

    }
}

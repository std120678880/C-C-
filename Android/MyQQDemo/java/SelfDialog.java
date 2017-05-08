package com.example.dada.myqqdemo;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class SelfDialog extends Dialog{

    private Button okButton;
    private TextView tipText;
    private TextView contentText;
    private String tipStr,contentStr;
    private OkOnClickListener okOnClickListener;

    public SelfDialog(Context context){
        super(context,R.style.dialog);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dialog_style);
        okButton = (Button)findViewById(R.id.dialog_button);
        tipText = (TextView)findViewById(R.id.dialog_title_text);
        contentText = (TextView)findViewById(R.id.dialog_contain_text);

        InitData();

        okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(okOnClickListener != null){
                    okOnClickListener.OkOnClick();
                }
            }
        });
    }

    //设置按钮的监听
    public void setClickListener(OkOnClickListener okOnClickListener){
        this.okOnClickListener = okOnClickListener;
    }

    public void setTipText(String title){
        tipStr = title;
    }

    public void setContentText(String title){
        contentStr = title;
    }

    public void InitData(){
        if(tipStr != null){
            tipText.setText(tipStr);
        }
        if(contentStr != null){
            contentText.setText(contentStr);
        }
    }

    public interface OkOnClickListener{
        public void OkOnClick();
    }
}


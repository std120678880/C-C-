package com.example.dada.myqqdemo;

import android.app.ActionBar;
import android.app.Activity;
import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.PopupWindow;

public class Login_bottom_menu extends PopupWindow{

    private View menuView;
    private Button login_bottom_findPassword;
    private Button login_bottom_messageLogin;
    private Button login_bottom_cancel;

    public Login_bottom_menu(Activity context, View.OnClickListener onClick){
        super(context);

        LayoutInflater inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        menuView = inflater.inflate(R.layout.login_bottom_menu,null);

        login_bottom_cancel = (Button)menuView.findViewById(R.id.login_bottom_menu_cancel);
        login_bottom_findPassword = (Button)menuView.findViewById(R.id.login_bottom_menu_findPassword);
        login_bottom_messageLogin = (Button)menuView.findViewById(R.id.login_bottom_menu_messageLogin);

        login_bottom_cancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dismiss();
            }
        });
        login_bottom_findPassword.setOnClickListener(onClick);
        login_bottom_messageLogin.setOnClickListener(onClick);

        this.setContentView(menuView);                //弹出窗体View
        this.setWidth(LayoutParams.MATCH_PARENT);     //弹出窗体宽
        this.setHeight(LayoutParams.WRAP_CONTENT);    //弹出窗体高
        this.setFocusable(true);                      //弹出窗体可点击
        this.setAnimationStyle(R.style.login_bottom_dialog);   //弹出窗体动画效果
        ColorDrawable dw = new ColorDrawable(0xb0000000);
        this.setBackgroundDrawable(dw);               //弹出窗体背景（半透明）
        menuView.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int height = menuView.findViewById(R.id.login_bottom_layout).getHeight();
                int y = (int)event.getY();
                if(event.getAction()==MotionEvent.ACTION_UP){
                    if(y < height){
                        dismiss();
                    }
                }
                return true;
            }
        });
    }
}

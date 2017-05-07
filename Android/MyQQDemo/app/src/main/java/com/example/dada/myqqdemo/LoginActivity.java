package com.example.dada.myqqdemo;

import android.app.*;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.support.design.widget.Snackbar;
import android.support.v4.app.*;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import com.androidadvance.topsnackbar.TSnackbar;

import org.litepal.crud.DataSupport;

import java.util.List;

public class LoginActivity extends BaseActivity {

    private CheckBox checkBox;
    private Button loginButton;
    private EditText userEdit,passwordEdit;
    private SelfDialog selfDialog;
    private TextView forgetPassword;
    private Button login_bottom_findPassword,login_bottom_messageLogin,login_bottom_cancel;
    private Login_bottom_menu menuWindow;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        checkBox = (CheckBox) findViewById(R.id.login_servicecheckBox);
        loginButton = (Button)findViewById(R.id.login_loginButton);
        userEdit = (EditText) findViewById(R.id.login_NumberEdit);
        passwordEdit = (EditText)findViewById(R.id.login_passwordEdit);
        forgetPassword = (TextView)findViewById(R.id.login_forgetPasswordText);

        WriteNewUserData("admin","123456");
    }

    //按下Back键结束程序
    @Override
    public void onBackPressed() {
        super.onBackPressed();
        ActivityCollector.finishAll();
    }

    @Override
    protected void onStart() {
        super.onStart();


        //设置checkBox初始值为选中状态
        checkBox.setChecked(true);
        //监听checkBox
        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    loginButton.setTextColor(Color.WHITE);
                    loginButton.setEnabled(true);
                } else {
                    loginButton.setTextColor(Color.GRAY);
                    loginButton.setEnabled(false);
                }
            }
        });

        //监听忘记密码TextView
        forgetPassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Setup_login_bottom_menu(new login_bottom_listener());
            }
        });

        //监听登录按钮
        //TSnackbar  从顶部显示消息提示栏
        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (userEdit.getText().toString().length() == 0) {
                    TSnackbar snackbar = TSnackbar.make(loginButton, "请输入账号。", Snackbar.LENGTH_SHORT);
                    SetupSnackbar(snackbar);
                    snackbar.show();
                } else if (passwordEdit.getText().toString().length() == 0) {
                    TSnackbar snackbar = TSnackbar.make(loginButton, "请输入密码。", Snackbar.LENGTH_SHORT);
                    SetupSnackbar(snackbar);
                    snackbar.show();
                } else {
                    /*
                    //消息提示框
                    selfDialog = new SelfDialog(LoginActivity.this);
                    selfDialog.setTipText("登陆失败");
                    selfDialog.setContentText("账号或密码错误，请重新输入。");
                    selfDialog.setClickListener(new SelfDialog.OkOnClickListener(){
                        public void OkOnClick(){
                            selfDialog.dismiss();
                        }
                    });
                    selfDialog.show();
                    */
                    boolean IsLogin = false;
                    selfDialog = new SelfDialog(LoginActivity.this);
                    selfDialog.setClickListener(new SelfDialog.OkOnClickListener(){
                        public void OkOnClick(){
                            selfDialog.dismiss();
                        }
                    });
                    String qq_number = userEdit.getText().toString();
                    String password  = passwordEdit.getText().toString();

                    List<UserDataBook> books = DataSupport.findAll(UserDataBook.class);
                    for(UserDataBook book: books){
                        if(book.getQQ_number().equals(qq_number)){
                            if(book.getPassword().equals(password)){
                                //登陆成功，向服务器提取数据并传输
                                //Toast.makeText(LoginActivity.this, "登陆成功", Toast.LENGTH_SHORT).show();

                                new Thread(new Runnable() {
                                    @Override
                                    public void run() {
                                        Intent intent = new Intent(LoginActivity.this, FragmentMain.class);
                                        startActivity(intent);
                                    }
                                }).start();
                                IsLogin = true;
                                break;
                            }
                            //密码错误
                            else{
                                selfDialog.setTipText("登陆失败");
                                selfDialog.setContentText("账号或密码错误，请重新输入。");
                                selfDialog.show();
                                IsLogin = true;
                                break;
                            }
                        }
                        //本地数据库不存在用户数据
                        else{
                            continue;
                        }
                    }
                    if(IsLogin == false){
                        //本地数据库不存在用户数据，向服务器查询用户账户数据并写入本地数据库
                    }
                    else{
                        //登陆成功
                        //向服务器提取用户所有数据信息
                    }
                }
            }
        });
    }

    //自定义设置Snackbar样式
    private void SetupSnackbar(TSnackbar snackbar) {
        LinearLayout snackbarView = (LinearLayout) snackbar.getView();//获取Snackbar布局View实例
        TextView textview = (TextView) snackbarView.findViewById(R.id.snackbar_text);//获取文本View实例
        View add_view = LayoutInflater.from(snackbarView.getContext()).inflate(R.layout.login_warning_image, null);
        snackbarView.addView(add_view, 0);
        //设置Snackbar背景颜色和字体颜色
        snackbarView.setBackgroundColor(Color.parseColor("#ffffff"));
        textview.setTextColor(Color.parseColor("#000000"));
        textview.setTextSize(20);
    }

    //找回密码和手机号登录选项
    class login_bottom_listener implements View.OnClickListener{
        @Override
        public void onClick(View v) {
            menuWindow.dismiss();
            switch (v.getId()){
                case R.id.login_bottom_menu_findPassword:
                {
                    Intent intent = new Intent(LoginActivity.this,Find_Password.class);
                    startActivity(intent);
                    break;
                }
                case R.id.login_bottom_menu_messageLogin:
                {
                    Intent intent = new Intent(LoginActivity.this,Phone_Login.class);
                    startActivity(intent);
                    break;
                }
                default:
                    break;
            }
        }
    }

    //底部菜单栏显示
    public void Setup_login_bottom_menu(View.OnClickListener onClickListener){
        //实例化
        menuWindow = new Login_bottom_menu(LoginActivity.this,onClickListener);
        //显示窗口
        menuWindow.showAtLocation(LoginActivity.this.findViewById(R.id.login_NumberEdit),Gravity.BOTTOM|Gravity.CENTER_HORIZONTAL,0 , 0);

    }

    //添加初始的用户账户数据
    public void WriteNewUserData(String num, String password){
        UserDataBook book = new UserDataBook();
        book.setQQ_number(num);
        book.setPassword(password);
        book.save();
    }
}


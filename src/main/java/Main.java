import okhttp3.*;

import java.io.IOException;

public class Main {
    public static void sendHttpRequest(String address,okhttp3.Callback callback){
        OkHttpClient client=new OkHttpClient();
        Request request=new Request.Builder().url(address).build();
        client.newCall(request).enqueue(callback);
    }

    public static void main(String args[]){
        makeATest();
        String url="http://guolin.tech/api/china";
        OkHttpClient client=new OkHttpClient();
        Request request=new Request.Builder().url(url).build();
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                System.out.println("Error!");
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                String result=response.body().string();
                System.out.println(result);
            }
        });
    }

    public static void makeATest(){
        System.out.println("This is a test system");
    }


}



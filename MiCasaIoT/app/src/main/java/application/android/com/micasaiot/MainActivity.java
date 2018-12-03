package application.android.com.micasaiot;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    private TextView tempTxVw;
    private TextView humidityTxVw;
    private TextView lightTxVw;
    private TextView rainTxVw;

    DatabaseReference ref = FirebaseDatabase.getInstance().getReference();
    DatabaseReference temperaturaRef = ref.child("temperatura");
    DatabaseReference humedadRef = ref.child("humedad");
    DatabaseReference luzRef = ref.child("luz");
    DatabaseReference lluviaRef = ref.child("lluvia");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tempTxVw = findViewById(R.id.tempTxVw);
        humidityTxVw = findViewById(R.id.humidityTxVw);
        lightTxVw = findViewById(R.id.lightTxVw);
        rainTxVw = findViewById(R.id.rainTxVw);
    }

    @Override
    protected void onStart() {
        super.onStart();

        temperaturaRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Integer value =  dataSnapshot.getValue(Integer.class);
                tempTxVw.setText(value.toString() + " °C");
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });

        humedadRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Integer value =  dataSnapshot.getValue(Integer.class);
                humidityTxVw.setText(value.toString() + " %");
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });

        luzRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Integer value =  dataSnapshot.getValue(Integer.class);
                lightTxVw.setText(value.toString() + " %");
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });

        lluviaRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value = dataSnapshot.getValue(String.class);
                rainTxVw.setText(value);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }
}

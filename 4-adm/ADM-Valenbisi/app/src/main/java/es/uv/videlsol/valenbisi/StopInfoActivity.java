package es.uv.videlsol.valenbisi;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;

import java.util.List;

/**
 * Created by Marcos on 21/03/2017.
 */

public class StopInfoActivity extends AppCompatActivity {
    private StopInfo stopInfo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.stop_info);

        stopInfo = (StopInfo) getIntent().getSerializableExtra("stop");

        getSupportActionBar().setTitle(stopInfo.getName());
        ((TextView) findViewById(R.id.stop_id)).setText(Integer.toString(stopInfo.getNumber()));
        ((TextView) findViewById(R.id.address)).setText(stopInfo.getAddress());
        ((TextView) findViewById(R.id.slots_free)).setText(Integer.toString(stopInfo.getFreeSlots()));
        ((TextView) findViewById(R.id.slots_total)).setText(Integer.toString(stopInfo.getTotalSlots()));
        ((TextView) findViewById(R.id.slots_used)).setText(Integer.toString(stopInfo.getUsedSlots()));
        ((TextView) findViewById(R.id.coords)).setText(stopInfo.getCoordinates().toString());

        ((ImageButton) findViewById(R.id.map_button)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent mapIntent = new Intent(Intent.ACTION_VIEW, stopInfo.getCoordinatesUri());
                startActivity(mapIntent);
            }
        });

        ((ImageButton) findViewById(R.id.new_report_button)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent mapIntent = new Intent(StopInfoActivity.this, ReportActivity.class);
                mapIntent.putExtra("report", new Report(stopInfo.getNumber()));
                startActivity(mapIntent);
            }
        });

        ReportDBHelper reportHelper = new ReportDBHelper(getApplicationContext());
        List<Report> stopReports = reportHelper.findByStop(stopInfo);
        ((ListView) findViewById(R.id.report_list)).setAdapter(new ReportCursorAdapter(getApplicationContext(), stopReports));
    }
}
package es.uv.videlsol.valenbisi;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

public class StopListActivity extends AppCompatActivity {
    private StopDatabase stops;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.stop_list_view);

        try {
            stops = new StopDatabase(IOUtil.readResourceAsString(this, R.raw.valenbisi_stops)).sortByAddress();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        ListView stopList = (ListView) findViewById(R.id.stop_list_entries);
        stopList.setAdapter(new StopListAdapter(this, stops));

        stopList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent = new Intent(StopListActivity.this, StopInfoActivity.class);
                intent.putExtra("stop", StopListActivity.this.stops.list().get(position));
                startActivity(intent);
            }
        });
    }
}

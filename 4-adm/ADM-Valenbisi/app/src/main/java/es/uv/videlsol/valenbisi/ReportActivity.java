package es.uv.videlsol.valenbisi;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Spinner;
import android.widget.TextView;

/**
 * Created by Marcos on 28/03/2017.
 */

public class ReportActivity extends AppCompatActivity {

    private Report report;

    private TextView subjectView;
    private TextView descriptionView;
    private Spinner typeSpinner;
    private Spinner statusSpinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.report_info);

        subjectView = (TextView) findViewById(R.id.report_subject);
        descriptionView = (TextView) findViewById(R.id.report_desc);
        typeSpinner = (Spinner) findViewById(R.id.report_type);
        statusSpinner = (Spinner) findViewById(R.id.report_status);

        report = (Report) getIntent().getSerializableExtra("report");
        subjectView.setText(report.getSubject());
        descriptionView.setText(report.getDescription());
        typeSpinner.setSelection(report.getType().ordinal());
        statusSpinner.setSelection(report.getStatus().ordinal());

        ((FloatingActionButton) findViewById(R.id.report_save_button)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ReportDBHelper helper = new ReportDBHelper(getApplicationContext());
                helper.saveReport(report);
                finish();
            }
        });

        ((FloatingActionButton) findViewById(R.id.report_delete_button)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ReportDBHelper helper = new ReportDBHelper(getApplicationContext());
                helper.deleteReport(report);
                finish();
            }
        });
    }
}
